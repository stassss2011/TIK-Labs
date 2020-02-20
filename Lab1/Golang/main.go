package main

import (
	"bufio"
	"fmt"
	"io"
	"math"
	"os"
	"sync"
)

func main() {
	var wg sync.WaitGroup
	ioBuffer := make(chan []byte)
	fileSizeChan := make(chan int, 1)
	syncChan := make(chan bool)
	wg.Add(2)
	var freqArr [256]float64
	go readFile("/home/stas/Загрузки/Star.Wars.Episode.VIII.The.Last.Jedi.2017.BluRay.1080p.Proper._BLUEBIRD.mkv", &wg, ioBuffer, fileSizeChan)
	go processFile(&wg, ioBuffer, &freqArr)
	wg.Wait()
	fmt.Println(freqArr)
	fileSize := <-fileSizeChan
	var sum float64
	for index, value := range freqArr {
		freqArr[index] = value / float64(fileSize)
	}
	for _, value := range freqArr {
		if value > 0.0 {
			sum -= value * math.Log2(value)
		}
	}
	fmt.Println(sum)
}

func readFile(fileName string, wg *sync.WaitGroup, ioBuffer chan []byte, fileSizeChan chan int, syncChan chan bool) {
	defer (*wg).Done()
	file, err := os.Open(fileName)
	if err != nil {
		fmt.Println("Unable to open file:", err)
		os.Exit(1)
	}
	defer file.Close()
	fmt.Println(file.Name())
	reader := bufio.NewReader(file)
	fileStat, err := file.Stat()
	if err != nil {
		fmt.Println("Cant get file size")
		os.Exit(1)
	}
	fileSize := int(fileStat.Size())
	fileSizeChan <- fileSize
	close(fileSizeChan)
	var chunkSize int
	if fileSize < 1048576 {
		chunkSize = fileSize
	} else {
		chunkSize = 1048576
	}
	buffer := make([]byte, chunkSize)
	var readCnt int

	for {
		_, err := reader.Read(buffer)
		if err != nil {
			if err == io.EOF {
				break
			} else {
				fmt.Println(err)
				return
			}
		}
		readCnt++
		var out []byte
		if fileSize == chunkSize{
			out = buffer[0:fileSize-1]
		}else if fileSize-readCnt*chunkSize < chunkSize {
			out = buffer[0 : fileSize-(readCnt)*chunkSize-1]
		} else {
			out = buffer[0 : chunkSize-1]
		}
		ioBuffer <- out
		//fmt.Println(buffer)
	}
	//fmt.Println(buffer)
	//close(ioBuffer)
}

func processFile(wg *sync.WaitGroup, ioBuffer chan []byte, freqArr *[256]float64) {
	defer (*wg).Done()
	var buffer []byte
	for {
		buffer, ok <- ioBuffer
		for _, value := range buffer {
			freqArr[value]++
		}
	}
}
