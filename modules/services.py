from textual.widgets import Static
from textual.containers import Vertical

class ServicesModule(Vertical):
    """Widget untuk memantau status Layanan (Sbox, Clean, etc)"""
    def compose(self):
        yield Static("[2] SERVICES & OPERATIONS", classes="sub-header")
        yield Static(" SBOX: STANDBY\n CLEAN: READY\n ZT-MESH: ACTIVE", id="service-status")

    def update_services(self, data: dict):
        sbox_stat = data.get("env_status", {}).get("sbox", {}).get("status", "STANDBY")
        color = "[#00ff00]" if sbox_stat == "Operational" else "[#ffff00]"
        status_text = (
            f" SBOX: {color}{sbox_stat}[/]\n"
            f" CLEAN: [#00ff00]READY[/]\n"
            f" ZT-MESH: [#00ff00]ACTIVE[/]"
        )
        self.query_one("#service-status").update(status_text)
