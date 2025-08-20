import cantools

# Load the DBC file
db = cantools.database.load_file("uart_com.dbc")

# Messages you want to document
target_msgs = ["ChargeControl2", "ChargeState2", "PT1000State", "FirmwareVersion", "GitHash", "InquiryPacket"]

# Sender name mapping
sender_name_map = {
    "CCY_SafetyController": "Safety Controller",
    "CCY_Linux": "Linux Processor"
}

# Senders to exclude from display
excluded_senders = {"Default_SafetyController"}

# Extract a signal row as a list of strings
def signal_row(signal):
    def safe(value):
        if value is None or str(value).strip() == "":
            return ""
        return str(value).strip()
    
    if signal.byte_order == "little_endian" and signal.length > 8:
        byte_order = "Little Endian"
    elif signal.byte_order == "big_endian" and signal.length > 8:
        byte_order = "Big Endian"
    else:
        byte_order = ""

    return [
        safe(signal.name),
        safe(signal.start),
        safe(signal.length),
        byte_order,
        "Yes" if signal.is_signed else "No",
        safe(signal.scale),
        safe(signal.offset),
        safe(signal.unit),
        signal.comment.strip() if signal.comment else "*No description available*"
    ]

def format_bit_matrix(msg):
    bit_width = 20
    byte_label_width = 3
    bitfield = [None] * (msg.length * 8)

    for signal in msg.signals:
        if signal.byte_order == "little_endian":
            bit_indices = list(range(signal.start, signal.start + signal.length))
        else:
            bit_indices = list(range(signal.start, signal.start - signal.length, -1))

        for idx in bit_indices:
            if 0 <= idx < len(bitfield):
                bitfield[idx] = signal.name

    total_bits = msg.length * 8
    num_rows = total_bits // 8
    lines = []

    # Header with byte index
    border = "   +" + "+".join(["-" * bit_width] * 8) + "+"
    header = "   |" + "|".join([f"{7 - i:^{bit_width}}" for i in range(8)]) + "|"
    lines.extend([border, header, border])

    for row in range(num_rows):
        base = row * 8
        seen = set()
        row_cells = []
        for i in range(8):
            bit_index = base + (7 - i)
            label = bitfield[bit_index]
            if label and label not in seen:
                cell = label[:bit_width].center(bit_width)
                seen.add(label)
            else:
                cell = " " * bit_width
            row_cells.append(cell)
        lines.append(f"{row:>3}|" + "|".join(row_cells) + "|")
        lines.append(border)

    rst = "\n**Bitfield Layout**\n\n::\n\n"
    rst += "\n".join(lines) + "\n"
    return rst


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

    rst += format_bit_matrix(msg)

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
