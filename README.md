# Linux Process Tree Kernel Module 🌲🧠

This project is a **Linux Kernel Module** that recursively lists processes in a **tree structure** starting from the `init` process (PID 1). It also logs the **code segment memory addresses** for each process. 

---

## 🧩 Features

- Displays process hierarchy in a readable, indented tree format.
- Includes:
  - **Process Name**
  - **PID**
  - **Code Segment Memory Addresses** (start and end)
- Uses `for_each_process()` and `task_struct` traversal.
- Outputs results using `printk()` to kernel logs.

---

## 📦 Files

- `process_tree_module.c`: Main kernel module source file.
- `Makefile`: For compiling the kernel module.

---

## 🧠 Concepts Used

- Linux Kernel Modules
- `task_struct` traversal
- Process tree hierarchy
- Kernel memory segment inspection
- Kernel logs via `printk()`

---

## 🛠️ Build and Load Instructions

```bash
make             # Build the module
sudo insmod process_tree_module.ko    # Insert the module
dmesg | tail -n 100   # Check the kernel logs for output
sudo rmmod process_tree_module        # Remove the module
make clean        # Clean build artifacts

📄 License
Licensed under the GPL (General Public License).

