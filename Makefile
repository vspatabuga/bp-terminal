build:
	go build -o bp-control cmd/bp-control/main.go

run: build
	./bp-control

clean:
	rm -f bp-control

# Perintah khusus untuk deploy ke node ARM (Trident/Android)
build-arm:
	GOOS=linux GOARCH=arm64 go build -o bp-control-arm cmd/bp-control/main.go
