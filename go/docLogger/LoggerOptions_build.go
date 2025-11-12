package docLogger

import (
	"time"
)

type OptionsBuilder struct {
	outputConsole bool
	outputFile    bool
	fileName      string
	timeProvider  func() time.Time
}

func NewOptionsBuilder() (ropbd *OptionsBuilder) {
	return &OptionsBuilder{
		outputConsole: true,
		outputFile:    true,
		fileName:      "",
		timeProvider:  func() time.Time { return time.Now() },
	}
}

func (opbd *OptionsBuilder) SetOutputConsole(oc bool) (ropbd *OptionsBuilder) {
	opbd.outputConsole = oc
	return opbd
}

func (opbd *OptionsBuilder) SetOutputFile(of bool) (ropbd *OptionsBuilder) {
	opbd.outputFile = of
	return opbd
}

func (opbd *OptionsBuilder) SetFileName(name string) (ropbd *OptionsBuilder) {
	opbd.fileName = name
	return opbd
}

func (opbd *OptionsBuilder) SetTimeProvider(tp func() time.Time) (ropbd *OptionsBuilder) {
	opbd.timeProvider = tp
	return opbd
}

func (opbd *OptionsBuilder) Build() *LoggerOptions {
	return NewLoggerOptions(opbd.outputConsole, opbd.outputFile, opbd.fileName, opbd.timeProvider)
}
