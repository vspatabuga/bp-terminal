# 🏴‍☠️ Black-Pearl Control Center (BP-TUI)

![Go](https://img.shields.io/badge/Go-00ADD8?style=for-the-badge&logo=go&logoColor=white)
![Bubble Tea](https://img.shields.io/badge/Bubble%20Tea-Charm-00ADD8?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)

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
