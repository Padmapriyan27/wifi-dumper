# Wi-Fi Credential Dump Tool (Windows)

A modular Wi-Fi credential dumping tool for Windows written in C — built using `netsh wlan` commands. Purpose-buil for real-world simulation and Wi-Fi forensics

## ⚙️ Features

- Dumps all saved Wi-Fi profiles with passwords
- Captures interface info, driver details, hosted network, autoconfig, filters, and available networks
- Writes all outputs to a single file (`wifi_dump.txt`)


## 🔧 Requirements

- Windows OS
- Admin privileges [for password dump] (Optional)
- `gcc` (via MinGW, TDM-GCC, or MSYS2)

## 🚀 Build Instructions

1. Install [MinGW](https://sourceforge.net/projects/mingw/) or similar GCC compiler
2. Ensure `gcc` is in your system PATH
3. Clone or download this project
4. Double-click `build.bat` or run in CMD:

```bash
build.bat
````

It creates:

```
wifi_dumper.exe
```

## 🧪 Run the Tool

Open a terminal as Admin and run:

```bash
wifi_dumper.exe
```

It generates:

```
result.txt
```

## 📌 Notes

* This tool is for **educational & simulation** use only
* Use responsibly and only on machines you own or have explicit permission to analyze

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## 👨‍💻 Author

**0xD4rkEYe** — Cybersecurity Researcher & Developer
