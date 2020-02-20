# coding=utf-8
import math
import os
from tqdm import tqdm
import fire


def cnt_freq(chunk, freq_list):
    for byte in chunk:
        freq_list[ord(byte)] += 1


def cnt_entropy(
        file_name="/home/stas/Загрузки/Star.Wars.Episode.VIII.The.Last.Jedi.2017.BluRay.1080p.Proper._BLUEBIRD.mkv",
        show_list=False, csv=False, csv_file_name="result.csv"):
    file_size = os.path.getsize(file_name)
    if file_size < 1048576:
        chunk_size = file_size
    else:
        chunk_size = 1048576
    print("File size in bytes: {}".format(file_size))
    print("Calculating Shannon entropy of file. Please wait...")
    freq_list = [0] * 256
    with tqdm(total=file_size, dynamic_ncols=True, unit_scale=True, unit="B") as p_bar:
        with open(file_name, "rb") as file:
            for chunk in iter(lambda: file.read(chunk_size), b''):
                cnt_freq(chunk, freq_list)
                p_bar.update(len(chunk))
    freq_list = list(map(lambda x: x / file_size, freq_list))
    ent = 0.0
    for freq in freq_list:
        if freq > 0:
            ent = ent - freq * math.log(freq, 2)
    inform_cap = int(math.ceil(ent) * file_size / 8)
    print("Shannon entropy: {}\nInformation capacity: {}".format(ent, inform_cap))
    with open(csv_file_name, "w") as file:
        for i in range(256):
            if show_list:
                print("\t{}:{} = {}".format(i, chr(i), freq_list[i]))
            if csv:
                file.write("{},{},{}\n".format(i, chr(i), freq_list[i]))


if __name__ == '__main__':
    fire.Fire(cnt_entropy)
