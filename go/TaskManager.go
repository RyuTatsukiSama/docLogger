package main

import (
	"context"
	"log"

	"github.com/RyuTatsukiSama/docLogger/go/docLogger"
)

func main() {
	opts := docLogger.NewOptionsBuilder().Build()
	docLogger.SetGlobalLoggerOptions(opts)
	dlog, _, err := docLogger.NewLogger("Main", *opts, context.Background())
	if err != nil {
		log.Fatal(err)
	}

	dlog.Log(docLogger.Trace, "This is a trace")
	dlog.Log(docLogger.Debug, "This is a debug")
	dlog.Log(docLogger.Info, "This is a info")
	dlog.Log(docLogger.Warning, "This is a warning")
	dlog.Log(docLogger.Error, "This is a error")
	dlog.Log(docLogger.Critical, "This is a critical")
}
