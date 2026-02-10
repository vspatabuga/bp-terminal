# modules/network.py
from textual.widgets import Static
from textual.containers import Vertical

class NetworkModule(Vertical):
    """Widget khusus untuk memantau ZeroTrust Mesh"""
    
    def compose(self):
        yield Static("[1] ZEROTRUST NETWORK MESH", classes="sub-header")
        yield Static(" Latency: Connection Locked...", id="zt-graph")

    def update_zt(self, data: dict):
        status_color = "[#00ff00]SECURED[/]" if data.get("status") == "SECURED" else "[#ff0000]LOCKED[/]"
        text = (
            f" Status: {status_color}\n"
            f" VM-01: {data.get('vm1')}ms | VM-02: {data.get('vm2')}ms"
        )
        self.query_one("#zt-graph").update(text)
