#include <git2.h>
#include <stdio.h>

int main() {
    git_repository *repo = NULL;
    int error;

    // 初始化 libgit2
    git_libgit2_init();

    // 打开一个 Git 仓库
    error = git_repository_open(&repo, "../"); // 假设当前目录下有一个 Git 仓库

    if (error == 0) {
        // 打印仓库的路径
        printf("Repository path: %s\n", git_repository_path(repo));
        git_repository_free(repo);
    } else {
        // 如果打开仓库失败，打印错误信息
        fprintf(stderr, "Failed to open repository: %s\n", git_error_last()->message);
    }

    // 清理 libgit2
    git_libgit2_shutdown();

    return 0;
}