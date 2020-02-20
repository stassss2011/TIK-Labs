#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <chrono>
#include <iomanip>

void countChar(char *txt, unsigned long int chunk_len, std::vector<double> *frequency) {
    int l = 0;
    for (int i = 0; i < chunk_len; i++) {
        if (txt[i] < 0)
            l = txt[i] + 256;
        else
            l = txt[i];
        (*frequency)[l] += 1.0f;
    }
}

int main() {
    std::vector<double> frequency(256, 0);

    std::ifstream file(
            "/home/stas/Загрузки/Star.Wars.Episode.VIII.The.Last.Jedi.2017.BluRay.1080p.Proper._BLUEBIRD.mkv",
            std::ifstream::binary);

    if (!file) {
        throw file.exceptions();
    }

    file.seekg(0, std::ifstream::end);
    unsigned long long int file_size = file.tellg();
    file.seekg(0, std::ifstream::beg);

    char *buffer = new char[1048576];

    std::cout << "Reading " << file_size << " bytes..." << std::endl;

    unsigned long int chunk_len = 1048576;
    if (file_size < 1048576)
        chunk_len = file_size;
    int read_cnt = 0;

    float progress = 0.0;
    int barWidth = 70;

    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::system_clock::now();
    end = std::chrono::system_clock::now();
    while (read_cnt * chunk_len < file_size) {
        std::cout << std::setprecision(2) << progress * 100.0 << " % " << "[";
        int pos = barWidth * progress;
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) std::cout << "=";
            else if (i == pos) std::cout << ">";
            else std::cout << " ";
        }
        unsigned long int elapsed_mkseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        unsigned long int remain_time = static_cast<int>(std::floor(static_cast<float>(elapsed_mkseconds) / (1000000 * progress)));
        std::cout << "] " << std::setprecision(2) << std::fixed << static_cast<float>(read_cnt * chunk_len) / 1000
                  << "k/"
                  << static_cast<float>(file_size) / 1000 << "k [" << elapsed_mkseconds / 1000000 << "s < "
                  << remain_time << "s, "
                  << static_cast<float>(read_cnt * chunk_len) / (static_cast<float>(elapsed_mkseconds) / 1000000) / 1000000 << "MB/s]\r";
        std::cout.flush();
        if (file_size - chunk_len * read_cnt < chunk_len) {
            chunk_len = file_size - chunk_len * read_cnt;
            file.read(buffer, chunk_len);
            if (chunk_len > 0) {
                countChar(buffer, chunk_len, &frequency);
                end = std::chrono::system_clock::now();
                progress = 1.0;
            }
            break;
        }
        file.read(buffer, chunk_len);
        read_cnt++;
        countChar(buffer, chunk_len, &frequency);
        end = std::chrono::system_clock::now();
        progress = (static_cast<float>(read_cnt) * static_cast<float>(chunk_len)) / static_cast<float>(file_size);
    }

    std::cout << std::setprecision(2) << progress * 100.0 << " % " << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    int elapsed_seconds = std::chrono::duration_cast<std::chrono::microseconds>
            (end - start).count();
    int remain_time = static_cast<int>(std::floor(static_cast<float>(elapsed_seconds) / (100000 * progress)));
    std::cout << "] " << std::setprecision(2) << std::fixed << static_cast<float>(file_size) / 1000 << "k/"
              << static_cast<float>(file_size) / 1000 << "k [" << elapsed_seconds / 1000000 << "s < " << remain_time
              << "s, "
              << (static_cast<float>(file_size) / (elapsed_seconds / 1000000)) / 1000000 << "MB/s]\r";
    std::cout.flush();
    std::cout << std::endl;
    file.close();
    delete[] buffer;

    double ent = 0.0;
    for (int i = 0; i < 256; i++) {
        frequency[i] = frequency[i] / static_cast<double>(file_size);
        if (frequency[i] > 0)
            ent -= frequency[i] * log2(frequency[i]);
    }
    int inform_cap = static_cast<int>(ent * file_size / 8);
    std::cout << "Shannon entropy:" << std::setprecision(8) << ent << std::endl
              << "Information capacity: " << inform_cap << std::endl;
    return 0;
}
