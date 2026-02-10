# modules/environment.py
from textual.widgets import Static
from textual.containers import Vertical

class EnvironmentModule(Vertical):
    """Widget untuk memantau resource sistem secara berderet"""
    
    def compose(self):
        yield Static("[3] ENVIRONMENT STATUS", classes="sub-header")
        yield Static(" [BP]  CPU: -- | RAM: -- | TEMP: --\n [CTX] CPU: -- | RAM: --", id="env-status-content")

    def update_env(self, data: dict):
        bp = data.get("bp", {})
        ctx = data.get("cortex", {})
        sbox = data.get("sbox", {})

        env_text = (
            f" [BP]   CPU: {bp.get('cpu')} | RAM: {bp.get('ram')} | TEMP: {bp.get('temp')}\n"
            f" [CTX]  CPU: {ctx.get('cpu')} | RAM: {ctx.get('ram')}\n"
            f" [SBOX] STATUS: {sbox.get('status')}"
        )
        self.query_one("#env-status-content").update(env_text)
