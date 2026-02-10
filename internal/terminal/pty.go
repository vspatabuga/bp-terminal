// internal/terminal/pty.go

package terminal

import (
	"os"
	"os/exec"

	"github.com/creack/pty"
)

type Terminal struct {
	Ptmx *os.File
}

func Start() (*Terminal, error) {
	c := exec.Command("/bin/bash")
	ptmx, err := pty.Start(c)
	if err != nil {
		return nil, err
	}
	return &Terminal{Ptmx: ptmx}, nil
}

// Fungsi BARU untuk sinkronisasi ukuran
func (t *Terminal) SetSize(rows, cols uint16) error {
	return pty.Setsize(t.Ptmx, &pty.Winsize{
		Rows: rows,
		Cols: cols,
	})
}

func (t *Terminal) Read(p []byte) (n int, err error)  { return t.Ptmx.Read(p) }
func (t *Terminal) Write(p []byte) (n int, err error) { return t.Ptmx.Write(p) }
