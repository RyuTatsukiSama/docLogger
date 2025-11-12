package docLogger

import (
	"io"
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
	fileStream    *io.Writer
	timeProvider  func() time.Time
}

func NewLoggerOptions(bool, bool, string, func() time.Time) (opts *LoggerOptions) {

	return opts
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

func (opts LoggerOptions) GetFileStream() *io.Writer {
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
