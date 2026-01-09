package main

import (
	"github.com/RyuTatsukiSama/docLogger/go/docLogger"
)

func main() {
	opts := docLogger.NewOptionsBuilder().Build()
	docLogger.SetGlobalLoggerOptions(opts)
	dlog := docLogger.NewLogger("Main", *opts)

	dlog.Trace("This is a trace")
	dlog.Debug("This is a debug")
	dlog.Info("This is a info")
	dlog.Warning("This is a warning")
	dlog.Error("This is a error")
	dlog.Critical("This is a critical")
}
