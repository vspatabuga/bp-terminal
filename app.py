import json
import subprocess
from textual.app import App, ComposeResult
from textual.widgets import Footer, Label
from textual.containers import Container, Vertical
from textual import work

# Import Modul UI Independen (Arsitektur Modular)
from modules.network import NetworkModule
from modules.services import ServicesModule
from modules.environment import EnvironmentModule

class BlackPearlMonitor(App):
    """
    Dedicated Monitoring Unit [Modular Layer 1]
    Berfokus pada visualisasi telemetry data.
    """
    CSS_PATH = "app.tcss"
    BINDINGS = [("q", "quit", "Exit")]

    def compose(self) -> ComposeResult:
        yield Label("BLACK-PEARL MONITORING UNIT", id="header")
        with Container(id="main-container"):
            with Vertical(id="monitoring-panel", classes="column"):
                yield NetworkModule(id="mod-network")
                yield ServicesModule(id="mod-services")
                yield EnvironmentModule(id="mod-env")
        yield Footer()

    def on_mount(self) -> None:
        self.set_interval(2, self.refresh_data)

    @work(exclusive=True, thread=True)
    def refresh_data(self) -> None:
        try:
            result = subprocess.run(['bp-stats'], capture_output=True, text=True)
            if result.returncode == 0:
                data = json.loads(result.stdout)
                self.call_from_thread(self.distribute_data, data)
        except Exception:
            pass

    def distribute_data(self, data: dict) -> None:
        self.query_one("#mod-network").update_zt(data.get("zerotrust", {}))
        self.query_one("#mod-services").update_services(data)
        self.query_one("#mod-env").update_env(data.get("env_status", {}))

if __name__ == "__main__":
    app = BlackPearlMonitor()
    app.run()
