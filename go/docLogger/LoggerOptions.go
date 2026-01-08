package docLogger

import (
	"fmt"
	"io"
	"log"
	"os"
	"time"
)

var (
	gOpts *LoggerOptions
)

type LoggerOptions struct {
	outputConsole bool
	outputFile    bool
	fileName      string
	fileStream    io.Writer
	timeProvider  func() time.Time
}

func newLoggerOptions(oc bool, of bool, fName string, tp func() time.Time) *LoggerOptions {
	var fs io.Writer

	if oc {
		if fName == "" {
			fName = time.Now().Format("1970-30-12 00:00:00")
		}

		// check if the docLogs dir exist, if not create it
		info, err := os.Stat("/docLogs")
		if err != nil {
			log.Fatal(err)
			return &LoggerOptions{}
		} else if !info.IsDir() {
			err = os.MkdirAll("/docLogs/", 0700)
			if err != nil {
				log.Fatal(err)
				return &LoggerOptions{}
			}
		}

		// TODO : manage previous log

		fs, err = os.Create(fmt.Sprintf("/docLogs/%s.log", fName))
		if err != nil {
			log.Fatal(err)
			return &LoggerOptions{}
		}
	}

	return &LoggerOptions{
		outputConsole: oc,
		outputFile:    of,
		fileName:      fName,
		timeProvider:  tp,
		fileStream:    fs,
	}
}

func (opts LoggerOptions) IsOutputConsole() bool {
	return opts.outputConsole
}

func (opts LoggerOptions) IsOutputFile() bool {
	return opts.outputFile
}

func (opts LoggerOptions) GetFileName() string {
	return opts.fileName
}

func (opts LoggerOptions) GetFileStream() io.Writer {
	return opts.fileStream
}

func (opts LoggerOptions) GetTimeProvider() func() time.Time {
	return opts.timeProvider
}

func SetGlobalLoggerOptions(opts *LoggerOptions) {
	if gOpts != nil {
		*gOpts = *opts
	} else {
		os.Stderr.WriteString("Global Options already set")
	}
}
