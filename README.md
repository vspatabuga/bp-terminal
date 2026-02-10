# 🏴‍☠️ Black-Pearl Control Center (BP-TUI)

[![Go](https://img.shields.io/badge/Go-00ADD8?style=flat-square&logo=go&logoColor=white)](https://go.dev/)
[![Bubble Tea](https://img.shields.io/badge/TUI-Bubble%20Tea-B7A0E8?style=flat-square&logo=charm)](https://github.com/charmbracelet/bubbletea)
[![Lipgloss](https://img.shields.io/badge/UI-Lipgloss-FF5F87?style=flat-square)](https://github.com/charmbracelet/lipgloss)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=flat-square)](LICENSE)
[![Go Report Card](https://goreportcard.com/badge/github.com/vspatabuga/bp-terminal)](https://goreportcard.com/report/github.com/vspatabuga/bp-terminal)

![Go Version](https://img.shields.io/github/go-mod/go-version/vspatabuga/bp-terminal?style=for-the-badge&logo=go)
![Repo Size](https://img.shields.io/github/repo-size/vspatabuga/bp-terminal?style=for-the-badge&color=blueviolet)
![Last Commit](https://img.shields.io/github/last-commit/vspatabuga/bp-terminal?style=for-the-badge)

A high-performance, modular Text User Interface (TUI) built with Go and the Bubble Tea framework. Designed for autonomous system orchestration and secure command execution within the Patabuga Enterprises System (PES) ecosystem.

---

## 🏗 New Go-Native Architecture

This project has been migrated to a native Go implementation to leverage superior concurrency and direct PTY (Pseudoterminal) integration.

### Layer 1: Interface (Bubble Tea)
* Uses **Lipgloss** for a rigid, geometric UI layout.
* Features a **50/50 split pilar design** for simultaneous monitoring and execution.

### Layer 2: Virtual Terminal Emulator (vt10x)
* Integrates a **virtual buffer** to interpret raw ANSI escape sequences.
* Provides a **stable grid** that prevents terminal output from breaking the UI chassis.

### Layer 3: PTY Execution (creack/pty)
* **Direct bridge** to the native `/bin/bash` shell.
* **Real-time command execution** with synchronized window resizing (SIGWINCH).

---

## 🛠 Tech Stack

* **Language:** Go 1.24+
* **TUI Framework:** Bubble Tea
* **Styling:** Lipgloss
* **Terminal Emulation:** vt10x
* **PTY Logic:** creack/pty

---

## 🛡 Security & Resilience: Zero Trust

The BP-Control Center maintains its "Security-First" mindset:

* **Alternate Screen Buffer:** Runs in a dedicated buffer to keep your primary terminal history clean and secure.
* **Zero Trust Handshake:** Integrated monitoring for secure node verification.

---

## 🚀 Installation & Execution

### Clone & Setup:
```bash
git clone [https://github.com/vspatabuga/bp-terminal.git](https://github.com/vspatabuga/bp-terminal.git)
cd bp-terminal

## ⚖️ License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

Copyright (c) 2025 Virgiawan Sagarmata Patabuga
