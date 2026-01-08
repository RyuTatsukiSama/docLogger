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

	log.Log(docLogger.Debug, "This is a debug")
	log.Log(docLogger.Debug, "This is a debug")
}
