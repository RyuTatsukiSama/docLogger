package main

import (
	"os"
	"time"

	"github.com/RyuTatsukiSama/docLogger/docLogger"
)

func main() {
	var log docLogger.Logger

	log.RegisterOutputStream(os.Stdout)
	log.RegisterTimeProvider(func() time.Time { return time.Now() })

	log.Log(docLogger.Trace, "This is a trace")
	log.Log(docLogger.Debug, "This is a debug")
	log.Log(docLogger.Info, "This is a info")
	log.Log(docLogger.Warning, "This is a warning")
	log.Log(docLogger.Error, "This is a error")
	log.Log(docLogger.Critical, "This is a critical")
}
