package tui

import (
	"io"

	tea "github.com/charmbracelet/bubbletea"
)

// TerminalMsg menampung output mentah dari PTY
type TerminalMsg string

func (m Model) Init() tea.Cmd {
	return nil
}

func (m Model) Update(msg tea.Msg) (tea.Model, tea.Cmd) {
	switch msg := msg.(type) {

	// 1. INPUT KEYBOARD: Langsung diteruskan ke PTY
	case tea.KeyMsg:
		switch msg.String() {
		case "ctrl+c", "esc":
			return m, tea.Quit
		case "enter":
			m.Term.Write([]byte("\r"))
		case "backspace":
			m.Term.Write([]byte("\x7f"))
		case "tab":
			m.Term.Write([]byte("\t"))
		default:
			m.Term.Write([]byte(msg.String()))
		}

	// 2. WINDOW RESIZE: Sinkronisasi dimensi sasis, emulator, dan PTY
	case tea.WindowSizeMsg:
		m.Width = msg.Width
		m.Height = msg.Height

		// Hitung ruang pilar [TERMINAL] (Model 1)
		cols := (m.Width / 2) - 6
		rows := (m.Height - 10) / 2

		// Validasi agar tidak bernilai nol atau negatif
		if cols > 0 && rows > 0 {
			// Update dimensi di otak emulator
			m.VT.Resize(cols, rows)
			// Update dimensi di shell native (/bin/bash)
			m.Term.SetSize(uint16(rows), uint16(cols))
		}

	// 3. PTY OUTPUT: Disuntikkan ke dalam Virtual Buffer
	case TerminalMsg:
		// Emulator vt10x akan menafsirkan byte mentah (termasuk ANSI)
		_, err := io.WriteString(m.VT, string(msg))
		if err != nil {
			// Jika terjadi error pada buffer, sistem tetap jalan tanpa crash
			return m, nil
		}
	}

	return m, nil
}
