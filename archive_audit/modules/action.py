# modules/action.py
import os
from textual.widgets import Static, RichLog, Input
from textual.containers import Vertical
from textual import on

class ActionModule(Vertical):
    def compose(self):
        yield Static("[1] COMMAND GUIDELINES", id="guidelines", classes="sub-header")
        yield Static(" Welcome Capt. F2: Sbox | F3: Cortex", id="guide-content")
        
        with Vertical(id="terminal-panel"):
            yield RichLog(highlight=True, markup=True, id="term-log")
            yield Input(placeholder="vsp@black-pearl:~$ Enter command...", id="term-input")

    def update_guide(self, text: str):
        self.query_one("#guide-content").update(text)

    @on(Input.Submitted, "#term-input")
    def handle_command(self, event: Input.Submitted) -> None:
        cmd = event.value.strip()
        if cmd:
            log = self.query_one("#term-log")
            log.write(f"\n[bold green]vsp@black-pearl:~$[/] {cmd}")
            
            # Eksekusi tanpa timeout agar tidak error pada perintah panjang
            # Menggunakan os.popen untuk menangkap stream output secara lebih natural
            try:
                with os.popen(f"source ~/.bp-alias && {cmd} 2>&1") as pipe:
                    for line in pipe:
                        self.app.call_from_thread(log.write, line.strip())
            except Exception as e:
                log.write(f"[red]Error: {str(e)}[/]")
                
            self.query_one("#term-input").value = ""
