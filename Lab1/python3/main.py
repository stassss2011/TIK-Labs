# coding=utf-8
import math
import os

import fire
import matplotlib.pyplot as plt
from tqdm import tqdm


def cnt_freq(chunk, freq_list):
    for byte in chunk:
        freq_list[byte] += 1


def cnt_entropy(file_name="/home/stas/Загрузки/recovery.img", show_list=False, csv=False, csv_file_name="result.csv"):
    file_size = os.path.getsize(file_name)
    if file_size < 1048576:
        chunk_size = file_size
    else:
        chunk_size = 1048576
    print(f"File size in bytes: {file_size}")
    print("Calculating Shannon entropy of file. Please wait...")
    freq_list = [0] * 256
    with tqdm(total=file_size, dynamic_ncols=True, unit_scale=True, unit="B") as p_bar:
        with open(file_name, "rb") as file:
            for chunk in iter(lambda: file.read(chunk_size), b''):
                cnt_freq(chunk, freq_list)
                p_bar.update(len(chunk))
    freq_list = list(map(lambda x: x / file_size, freq_list))
    ent = 0.0
    alph = 0
    for freq in freq_list:
        if freq > 0:
            ent = ent - freq * math.log(freq, 2)
            alph += 1
    inform_cap = int(math.ceil(ent) * file_size / 8)
    plt.hist(x=range(256), bins=256, weights=freq_list)
    plt.savefig(file_name + '.png')
    print(f"Shannon entropy: {ent}\nInformation capacity: {inform_cap}\nAlphabed length: {alph}")
    with open(csv_file_name, "w") as file:
        for i in range(256):
            if show_list:
                print(f"\t{i}:{chr(i)} = {freq_list[i]}")
            if csv:
                file.write(f"{i},{chr(i)},{freq_list[i]}\n")


if __name__ == '__main__':
    fire.Fire(cnt_entropy)
