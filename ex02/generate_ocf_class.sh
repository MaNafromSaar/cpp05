#!/usr/bin/env bash

set -euo pipefail

trim() {
    local s="$1"
    s="${s#${s%%[![:space:]]*}}"
    s="${s%${s##*[![:space:]]}}"
    printf '%s' "$s"
}

contains_token() {
    local token="$1"
    shift
    local item
    for item in "$@"; do
        if [[ "$item" == "$token" ]]; then
            return 0
        fi
    done
    return 1
}

# Operators that live INSIDE the class body
build_member_operators() {
    local class_name="$1"
    shift
    local ops=("$@")
    local op

    for op in "${ops[@]}"; do
        case "$op" in
            "<<"|">>") ;; # free (non-member) operators — emitted outside the class
            "=="|"!="|"<"|">"|"<="|">=")
                printf '    bool operator%s(const %s& other) const;\n' "$op" "$class_name"
                ;;
            "++")
                printf '    void* operator++();          // TODO: choose meaningful return type\n'
                printf '    void* operator++(int);       // TODO: choose meaningful return type\n'
                ;;
            "--")
                printf '    void* operator--();          // TODO: choose meaningful return type\n'
                printf '    void* operator--(int);       // TODO: choose meaningful return type\n'
                ;;
            "[]")
                printf '    void* operator[](void* index);       // TODO: update index and return types\n'
                printf '    void* operator[](void* index) const; // TODO: update index and return types\n'
                ;;
            "()")
                printf '    void* operator()(void* arg);         // TODO: update argument and return types\n'
                printf '    void* operator()(void* arg) const;   // TODO: update argument and return types\n'
                ;;
            "=") ;; # OCF already includes copy-assignment
            *)
                printf '    void* operator%s(void* rhs) const; // TODO: update operand and return types\n' "$op"
                ;;
        esac
    done
}

# Operators that live OUTSIDE the class body (non-member free functions)
build_free_operators() {
    local class_name="$1"
    shift
    local ops=("$@")
    local op

    for op in "${ops[@]}"; do
        case "$op" in
            "<<")
                printf 'std::ostream& operator<<(std::ostream& os, const %s& obj); // TODO: implement in .cpp\n' "$class_name"
                ;;
            ">>")
                printf 'std::istream& operator>>(std::istream& is, %s& obj); // TODO: implement in .cpp\n' "$class_name"
                ;;
        esac
    done
}

printf 'Class name: '
IFS= read -r raw_class_name
class_name="$(trim "$raw_class_name")"

if [[ -z "$class_name" ]]; then
    echo "Error: class name cannot be empty."
    exit 1
fi

if [[ ! "$class_name" =~ ^[A-Za-z_][A-Za-z0-9_]*$ ]]; then
    echo "Error: invalid class name '$class_name'. Use a valid C++ identifier."
    exit 1
fi

hpp_file="${class_name}.hpp"

if [[ ! -f "$hpp_file" ]]; then
    guard="${class_name^^}_HPP"
    printf '#ifndef %s\n#define %s\n\n#endif\n' "$guard" "$guard" > "$hpp_file"
    echo "Created '$hpp_file'."
fi

if grep -Eq "^[[:space:]]*class[[:space:]]+${class_name}[[:space:]]*\b" "$hpp_file"; then
    echo "Error: class '$class_name' already appears in '$hpp_file'."
    exit 1
fi

printf 'Additional operators (space/comma separated, e.g. == != + <<): '
IFS= read -r raw_ops

normalized_ops="${raw_ops//,/ }"
read -r -a op_candidates <<< "$normalized_ops"

ops=()
for token in "${op_candidates[@]}"; do
    token="$(trim "$token")"
    [[ -z "$token" ]] && continue
    if ! contains_token "$token" "${ops[@]}"; then
        ops+=("$token")
    fi
done

member_op_lines=""
free_op_lines=""
if ((${#ops[@]} > 0)); then
    member_op_lines="$(build_member_operators "$class_name" "${ops[@]}")"
    free_op_lines="$(build_free_operators "$class_name" "${ops[@]}")"
fi

class_block="\n// ===== Auto-generated Orthodox Canonical Form (adjust placeholders as needed) =====\n"
class_block+="#include <string>\n"
class_block+="#include <iostream>\n"
class_block+="#include <sstream>\n"
class_block+="\nclass ${class_name}\n"
class_block+="{\n"
class_block+="private:\n"
class_block+="    // NOTE: Add meaningful private members here.\n"
class_block+="\npublic:\n"
class_block+="    ${class_name}();\n"
class_block+="    ${class_name}(const ${class_name}& other);\n"
class_block+="    ${class_name}& operator=(const ${class_name}& other);\n"
class_block+="    ~${class_name}();\n"

if [[ -n "$member_op_lines" ]]; then
    class_block+="\n    // NOTE: Placeholder signatures — update types/semantics to match real behavior.\n"
    while IFS= read -r line; do
        [[ -z "$line" ]] && continue
        class_block+="$line\n"
    done <<< "$member_op_lines"
fi

class_block+="};\n"

if [[ -n "$free_op_lines" ]]; then
    class_block+="\n// Non-member operators (free functions — cannot be class members):\n"
    while IFS= read -r line; do
        [[ -z "$line" ]] && continue
        class_block+="$line\n"
    done <<< "$free_op_lines"
fi

class_block+="// ===== End auto-generated block =====\n"

last_endif_line="$(grep -n '^[[:space:]]*#endif' "$hpp_file" | tail -n 1 | cut -d: -f1 || true)"

tmp_file="$(mktemp)"

if [[ -n "$last_endif_line" ]]; then
    if ((last_endif_line > 1)); then
        head -n "$((last_endif_line - 1))" "$hpp_file" > "$tmp_file"
    fi
    printf '%b' "$class_block" >> "$tmp_file"
    tail -n "+$last_endif_line" "$hpp_file" >> "$tmp_file"
else
    cat "$hpp_file" > "$tmp_file"
    printf '%b' "$class_block" >> "$tmp_file"
fi

cat "$tmp_file" > "$hpp_file"
rm -f "$tmp_file"

echo "Appended Orthodox Canonical Form class block for '$class_name' to '$hpp_file'."

# ── .cpp generation ──────────────────────────────────────────────────────────
cpp_file="${class_name}.cpp"

cpp_content="\n// ===== Auto-generated stubs for ${class_name} (append-only block) =====\n"
cpp_content+="#include \"${hpp_file}\"\n"
cpp_content+="\n// ── Orthodox Canonical Form ──────────────────────────────────────────────────\n"
cpp_content+="\n${class_name}::${class_name}()\n{\n}\n"
cpp_content+="\n${class_name}::${class_name}(const ${class_name}& other)\n{\n    *this = other;\n}\n"
cpp_content+="\n${class_name}& ${class_name}::operator=(const ${class_name}& other)\n{\n    if (this != &other)\n    {\n        // TODO: copy members\n    }\n    return *this;\n}\n"
cpp_content+="\n${class_name}::~${class_name}()\n{\n}\n"

 # member operator stubs
if [[ -n "$member_op_lines" ]]; then
    cpp_content+="\n// ── Member operators ─────────────────────────────────────────────────────────\n"
    while IFS= read -r sig; do
        [[ -z "$sig" ]] && continue
        sig="${sig#"${sig%%[![:space:]]*}"}"   # ltrim whitespace
        def="${sig%%;*}"                        # drop semicolon + trailing comment
        # prefix method name with ClassName::
        def="${def/operator/${class_name}::operator}"
        cpp_content+="\n${def}\n{\n    // TODO\n}\n"
    done <<< "$member_op_lines"
fi

 # free operator stubs
if [[ -n "$free_op_lines" ]]; then
    cpp_content+="\n// ── Non-member operators ─────────────────────────────────────────────────────\n"
    while IFS= read -r sig; do
        [[ -z "$sig" ]] && continue
        sig="${sig%%;*}"                        # drop semicolon + trailing comment
        cpp_content+="\n${sig}\n{\n    // TODO\n}\n"
    done <<< "$free_op_lines"
fi

cpp_content+="// ===== End auto-generated stubs for ${class_name} =====\n"

if [[ -f "$cpp_file" ]]; then
    printf '%b' "$cpp_content" >> "$cpp_file"
    echo "Appended stub implementations to existing '$cpp_file'."
else
    printf '%b' "$cpp_content" > "$cpp_file"
    echo "Created '$cpp_file' with stub implementations."
fi