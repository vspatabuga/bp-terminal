

# 🏴‍☠️ Black-Pearl Control Center (BP-TUI)

A sophisticated, modular Text User Interface (TUI) designed for autonomous system orchestration, infrastructure monitoring, and secure command execution. Built with a 3-layer architecture to manage the **Patabuga Enterprises System (PES)** ecosystem.

## 🏗 Architectural Framework

This project implements a strict **Separation of Concerns (SoC)** through a tri-layered approach:

1. **Layer 1: Presentation (TUI Shell)** Built using **Python Textual**, this layer serves as the command center's interface. It features a component-based design where UI elements (Network, Environment, Action) are isolated modules.
2. **Layer 2: Logic Hub (Alias Orchestration)** A centralized logic repository (`.bp-alias`) that translates human-readable commands into complex system operations. It acts as the "brain" between the interface and the OS.
3. **Layer 3: Execution (Data Harvesters & Binaries)** Low-level shell scripts and binaries located in `/usr/local/bin`. These "muscles" perform heavy lifting, such as telemetry gathering (JSON) and Azure Cloud management.

---

## 🛡 Security & Resilience: Zero Trust Integration

The BP-Control Center is designed with a **"Security-First"** mindset. The monitoring pilar integrates a Zero Trust Network Mesh status check:

* **Secure Lockdown:** If the Zero Trust handshake is lost, the TUI enters a "Locked" state, preventing command leakage to unauthorized networks.
* **Invisible Infrastructure:** By utilizing tunneling and IaC (Infrastructure as Code), the control center remains invisible to the public internet.

---

## 🛠 Tech Stack

* **Interface:** Python 3.10+, Textual, Rich.
* **Logic:** Bash (Functional Aliases), JSON.
* **Monitoring:** Linux Sys-fs, Ping-mesh, Azure CLI.
* **Ops:** Symlinked Monorepo for seamless system integration.

---

## 🚀 Installation & Setup

1. **Clone the Repository:**
```bash
git clone https://github.com/your-username/bp-terminal.git
cd bp-terminal

```


2. **Initialize System Bridging:**
The project uses symbolic links to integrate with your local system environment.
```bash
# Link the binaries
sudo ln -s $(pwd)/bin/bp-stats /usr/local/bin/bp-stats
# Link the logic hub
ln -s $(pwd)/logic/.bp-alias ~/.bp-alias

```


3. **Run the Control Center:**
```bash
python3 app.py

```



---

## 📜 Documentation & Chronology

Development is strictly logged in `DOCS.md`, detailing the system's evolution from a single-script harvester to a full-scale modular command center.

---


