# Cryptography_Frequency_Time_Project


This C mini project demonstrates a simple cryptography mechanism by encoding and decoding alphabetical characters (`A-Z`) based on **frequency (Hz)** and **time (ms)**. Each character is uniquely mapped to a (frequency, time) pair and can be encrypted or decrypted using this mapping.

---

## 📌 Features

- 🔤 Encrypt plain messages using frequency-time encoding.
- 🔓 Decrypt encoded signals back to original text.
- 📁 Read input from and write output to files:
  - `message.txt` – Input text to be encrypted.
  - `encrypted.txt` – Stores frequency-time encoded signals.
  - `decrypted.txt` – Stores the decrypted message.
- 🧑‍💻 Option to manually input messages and decode frequency-time values.
- ❎ Simple menu-driven console interface.

---

## ⚙️ How it Works

Each letter from `A-Z` is assigned:
- A **frequency**: starting from 100Hz, incrementing by 10Hz.
- A **time** duration: starting from 50ms, incrementing by 5ms.

| Letter | Frequency (Hz) | Time (ms) |
|--------|----------------|-----------|
| A      | 100            | 50        |
| B      | 110            | 55        |
| C      | 120            | 60        |
| ...    | ...            | ...       |
| Z      | 350            | 175       |

These values are used to encode and decode messages securely.

---

## 📂 File Structure

```plaintext
📁 Project Folder
│
├── cryptography.c       # Main source code
├── message.txt          # Sample input file
├── encrypted.txt        # Output: encoded frequency-time values
├── decrypted.txt        # Output: decoded original message
└── README.md            # Project documentation
