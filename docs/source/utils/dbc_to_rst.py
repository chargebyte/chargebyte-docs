import cantools

# Load the DBC file
db = cantools.database.load_file("uart_com.dbc")

# Messages you want to document
target_msgs = ["ChargeControl1", "ChargeState1", "PT1000State", "FirmwareVersion", "GitHash", "InquiryPacket"]

# Sender name mapping
sender_name_map = {
    "Default_SafetyController": "Safety Controller",
    "Default_Linux": "Linux Processor"
}

# Senders to exclude from display
excluded_senders = {"CCY_SafetyController"}

# Extract a signal row as a list of strings
def signal_row(signal):
    def safe(value):
        if value is None or str(value).strip() == "":
            return "-"
        return str(value).strip()

    return [
        safe(signal.name),
        safe(signal.start),
        safe(signal.length),
        "Little Endian" if signal.byte_order == "little_endian" else "Big Endian",
        "Yes" if signal.is_signed else "No",
        safe(signal.scale),
        safe(signal.offset),
        safe(signal.unit),
        signal.comment.strip() if signal.comment else "*No description available*"
    ]

# Format one message block as RST
def format_message_rst(msg):
    rst = f"{msg.name}\n{'=' * len(msg.name)}\n\n"
    rst += f"**ID**: 0x{msg.frame_id:X} ({msg.frame_id})\n\n"
    rst += f"**Length**: {msg.length} bytes\n\n"
    rst += f"**Description**: {msg.comment.strip() if msg.comment else 'N/A'}\n\n"

    # Map and filter senders
    senders = [sender_name_map.get(s, s) for s in msg.senders if s not in excluded_senders]
    rst += f"**Senders**: {', '.join(senders) if senders else 'N/A'}\n\n"

    # Table header
    rst += f".. list-table:: Signals in {msg.name}\n"
    rst += "   :widths: 30 6 6 10 7 7 7 6 30\n"
    rst += "   :header-rows: 1\n\n"

    headers = ["Name", "Start", "Length", "ByteOrder", "Signed", "Factor", "Offset", "Unit", "Description"]
    rst += "   * - " + "\n     - ".join(headers) + "\n"

    # Sort signals by start bit
    sorted_signals = sorted(msg.signals, key=lambda s: s.start)
    for sig in sorted_signals:
        row = signal_row(sig)
        rst += "   * - " + "\n     - ".join(row) + "\n"

    # Value descriptions (choices)
    choice_blocks = []
    for sig in sorted_signals:
        if sig.choices:
            lines = [f"  - 0x{int(k):X} = {v}" for k, v in sorted(sig.choices.items(), key=lambda x: int(x[0]), reverse=False)]
            choice_blocks.append(f"- **{sig.name}**\n\n" + "\n".join(lines))

    if choice_blocks:
        rst += "\n**Value Descriptions**\n\n" + "\n\n".join(choice_blocks) + "\n"

    return rst

# Generate RST output
output = ""
for target_name in target_msgs:
    msg = db.get_message_by_name(target_name)
    if msg:
        output += format_message_rst(msg) + "\n"
    else:
        print(f"Warning: Message '{target_name}' not found in DBC!")

# Write to file
with open("../safety_protocol.rst", "w", encoding="utf-8") as f:
    f.write(output)
