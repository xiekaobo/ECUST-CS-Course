#include"shell.h"

char **split_string_by_space(const char *input) {
    // 计算字符串的最大数量
    size_t max_tokens = strlen(input) / 2 + 1;
    char **res = malloc(max_tokens * sizeof(char *));
    if (res == NULL) {
        perror("malloc");
        return NULL;
    }

    // 拷贝输入字符串，因为strtok会修改字符串
    char *input_copy = strdup(input);
    if (input_copy == NULL) {
        perror("strdup");
        free(res);
        return NULL;
    }

    size_t token_index = 0;
    char *token = strtok(input_copy, " ");
    while (token != NULL) {
        // 计算当前token的长度以及它在原始字符串中的位置
        size_t token_len = strlen(token);
        const char *pos = strstr(input, token);

        // 保留原始字符串中的空格
        size_t spaces_after = 0;
        while (input + strlen(token) + spaces_after < input + strlen(input) && 
               *(pos + token_len + spaces_after) == ' ') {
            spaces_after++;
        }

        res[token_index] = malloc(token_len + spaces_after + 1);
        if (res[token_index] == NULL) {
            perror("malloc");
            for (size_t i = 0; i < token_index; i++) {
                free(res[i]);
            }
            free(res);
            free(input_copy);
            return NULL;
        }
        // 复制token并保留后面的空格
        strncpy(res[token_index], token, token_len);
        strncpy(res[token_index] + token_len, input + (pos - input) + token_len, spaces_after);
        res[token_index][token_len + spaces_after] = '\0';

        token_index++;
        token = strtok(NULL, " ");
    }
    
    // 设置最后一个指针为NULL，以便标记数组的结尾
    res[token_index] = NULL;

    free(input_copy);
    return res;
}

void free_split_result(char **res) {
    for (size_t i = 0; res[i] != NULL; i++) {
        free(res[i]);
    }
    free(res);
}