#include <iostream>
#include <getopt.h>
#include <string>

int main(int argc, char *argv[]) {
    int opt;
    std::string tag;
    std::string name;

    // 定义长选项结构体数组
    static struct option long_options[] = {
        {"tag", required_argument, 0, 't'},
        {"name", required_argument, 0, 'n'},
        {0, 0, 0, 0} // 结束标记
    };

    while ((opt = getopt_long(argc, argv, "t:n:", long_options, nullptr)) != -1) {
        switch (opt) {
            case 't':
                tag = optarg;
                break;
            case 'n':
                name = optarg;
                break;
            default:
                std::cerr << "Usage: " << argv[0] << " --tag=<tag_value> --name=<name_value>" << std::endl;
                return 1;
        }
    }

    // 检查是否成功解析参数
    if (tag.empty() || name.empty()) {
        std::cerr << "Invalid arguments. Usage: " << argv[0] << " --tag=<tag_value> --name=<name_value>" << std::endl;
        return 1;
    }

    // 输出解析结果
    std::cout << "Tag: " << tag << std::endl;
    std::cout << "Name: " << name << std::endl;

    return 0;
}
