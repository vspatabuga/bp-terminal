package tui

import (
	"bp-terminal/internal/terminal"

	"github.com/hinshun/vt10x"
)

// Model menyimpan seluruh state sistem Black Pearl.
// Menggunakan Virtual Terminal Emulator (VTE) untuk stabilitas grid.
type Model struct {
	// Mesin PTY untuk komunikasi dengan shell native
	Term *terminal.Terminal

	// VT adalah otak emulator yang menafsirkan byte mentah menjadi grid 2D
	VT vt10x.Terminal

	// Dimensi jendela dashboard yang diperbarui secara dinamis
	Width  int
	Height int

	// Status navigasi antar pilar/tab
	ActiveTab int
}

// NewModel menginisialisasi sasis baru dengan PTY yang sudah menyala.
func NewModel(t *terminal.Terminal) Model {
	// Inisialisasi emulator terminal virtual
	// Kita mulai dengan ukuran default, nantinya akan di-resize otomatis di Update loop.
	vt := vt10x.New()

	return Model{
		Term:      t,
		VT:        vt,
		ActiveTab: 1, // Default pilar aktif
	}
}
