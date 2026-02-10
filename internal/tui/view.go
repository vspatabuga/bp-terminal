package tui

import (
	"strings"

	"github.com/charmbracelet/lipgloss"
	"github.com/hinshun/vt10x"
)

var (
	// Header: Posisi kiri tengah, Bold, No Frame
	headerStyle = lipgloss.NewStyle().
			Bold(true).
			Foreground(lipgloss.Color("#FFFFFF")).
			Padding(1, 0, 1, 2) // Atas, Kanan, Bawah, Kiri

	// Style Window: Sesuai screenshot sebelumnya
	pilarStyle = lipgloss.NewStyle().
			Border(lipgloss.NormalBorder()).
			BorderForeground(lipgloss.Color("#555555"))

	// Frame Luar yang membungkus seluruh dashboard
	globalFrame = lipgloss.NewStyle().
			Border(lipgloss.NormalBorder()).
			BorderForeground(lipgloss.Color("#555555"))
)

func (m Model) View() string {
	if m.Width == 0 || m.Height == 0 {
		return "Initializing Black Pearl Control Panel..."
	}

	// 1. HEADER (Teks Lebar di Kiri)
	header := headerStyle.Render("B L A C K   P E A R L   C O N T R O L   P A N E L")

	// 2. KALIBRASI DIMENSI (Presisi internal)
	// Mengurangi space untuk Global Frame (-2) dan Header (-3)
	availableWidth := m.Width - 4
	availableHeight := m.Height - 6

	midX := availableWidth / 2
	pilarHeight := availableHeight / 2

	// --- PILAR KIRI (LOG & TERMINAL) ---
	logContent := "Standard Operating Procedure\nPES Protocol v1.0\nZeroTrust Layer Active"
	logWindow := pilarStyle.
		Width(midX - 2).
		Height(pilarHeight - 2).
		Render(logContent)

	// --- RENDER VIRTUAL TERMINAL (VTE) ---
	var termLines []string
	if state, ok := m.VT.(interface{ State() *vt10x.State }); ok {
		s := state.State()
		s.Lock()
		defer s.Unlock()
		cols, rows := s.Size()
		for i := 0; i < rows; i++ {
			var lineStr strings.Builder
			for j := 0; j < cols; j++ {
				glyph := s.Cell(j, i)
				if glyph.Char == 0 {
					lineStr.WriteRune(' ')
				} else {
					lineStr.WriteRune(glyph.Char)
				}
			}
			termLines = append(termLines, lineStr.String())
		}
	} else {
		termLines = strings.Split(m.VT.String(), "\n")
	}

	terminalView := pilarStyle.
		Width(midX - 2).
		Height(pilarHeight - 2).
		Render(strings.Join(termLines, "\n"))

	pilarKiri := lipgloss.JoinVertical(lipgloss.Left, logWindow, terminalView)

	// --- PILAR KANAN (DATA PANELS) ---
	rHeight := availableHeight / 3
	rWidth := availableWidth - midX

	intel := pilarStyle.Width(rWidth - 2).Height(rHeight - 2).Render("Status: SG-01 ACTIVE\nMode: Stealth Isolation")
	services := pilarStyle.Width(rWidth - 2).Height(rHeight - 2).Render("PES: 1.000.000 NODES\nOrchestrator: ACTIVE")
	env := pilarStyle.Width(rWidth - 2).Height(rHeight - 2).Render("CPU: STABLE\nMEM: OPTIMAL\nNODE: TRIDENT-01")

	pilarKanan := lipgloss.JoinVertical(lipgloss.Left, intel, services, env)

	// 3. ASSEMBLY AKHIR
	mainContent := lipgloss.JoinHorizontal(lipgloss.Top, pilarKiri, pilarKanan)

	// Gabungkan Header dan Content secara vertikal
	fullDashboard := lipgloss.JoinVertical(lipgloss.Left, header, mainContent)

	// Bungkus semuanya dengan Frame Global agar simetris
	return globalFrame.
		Width(m.Width - 2).
		Height(m.Height - 2).
		Render(fullDashboard)
}
