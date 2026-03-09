# Unreal Engine 5 C++ AI Developer Skill

A curated system prompt and instructions package designed specifically for modern **AI Coding Assistants** and **AI IDEs** (such as Cursor, Windsurf, Cline, Copilot, Antigravity, and others). 

By integrating this skill into your AI assistant, you force the AI to stop writing generic "standard C++" and start writing robust, memory-safe, high-performance C++ code that strictly adheres to the modern **Unreal Engine 5** ecosystem and design patterns.

## 🚀 Why Use This Skill?

Unreal Engine C++ relies on highly specific paradigms: garbage collection via `UObject`, macro reflection (`UCLASS`, `UPROPERTY`), subsystem decoupling, and heavy emphasis on memory efficiency. 

Out of the box, AI models often fail to grasp these idiosyncrasies without explicit instruction. They will try to use `std::vector` instead of `TArray`, raw pointers instead of `TObjectPtr`, and put heavy calculation logic inside `Tick()`.

**This skill explicitly course-corrects the AI**, demanding that standard C++ practices are swapped with Epic Games' strict C++ standards.

---

## 🛠️ Features Governed by the AI

When this skill is active, the AI will automatically enforce the following modern standards:

- **Pointer & Memory Safety:** Replaces generic raw pointers (`*`) with UE5 `TObjectPtr`. Utilizes proper GC macros and pointer validation macros (`IsValid`, `ensure`).
- **Data-Driven Architecture & Tags:** Prioritizes `UDataAsset` and `GameplayTags` over hardcoded configuration variables and enums inside Actors.
- **Enhanced Input System (EIS):** Strictly enforces `UEnhancedInputComponent` over deprecated Action/Axis mappings.
- **IWYU Protocol:** Actively uses Forward Declarations and minimizes header `#include`s, protecting compilation time.
- **Performance & Micro-optimizations:** Bypasses `std::` containers in gameplay code in favor of `TArray`, `TMap`, `FString`, `FText`, and `FName`. Uses `TInlineComponentArray` to avoid heap allocations.
- **Tick Elimination:** Forces `PrimaryActorTick.bCanEverTick = false` by default in constructors. Promotes event-driven designs (Timers and Delegates) over wasteful `Tick()` routines.
- **Asset References & Tuning:** Eliminates brittle hardcoded C++ asset paths (`FObjectFinder`) and "magic numbers". Forces exposing tuning values and assets via `UPROPERTY` or `TSoftObjectPtr`.
- **Blueprint Integration:** Accurately designates `BlueprintCallable`, `BlueprintPure`, and delegates via `BlueprintImplementableEvent` avoiding spaghetti architecture.

---

## 📂 Files Provided & Structure

- **`.agent/skills/unreal-cpp-developer/SKILL.md`**: The core set of rules. Your AI reads this to understand Unreal Engine.
- **`.agent/skills/unreal-cpp-developer/custom_rules.md`**: A dedicated file for **your team**. Add your project's naming conventions, specific macros, or class prefixes here. The AI will prioritize your custom rules over the base skill.
- **`.agent/skills/unreal-cpp-developer/templates/`**: Clean boilerplate templates for `.h` and `.cpp` files. The AI will use these when asked to generate a brand new class from scratch.

---

## ⚡ Installation & Usage

### For Antigravity, Cursor, Windsurf, Cline, and other Custom Agents
1. Download or clone this repository.
2. Copy the entire `.agent` folder into the root directory of your Unreal Engine project.
   *(E.g., `MyUEProject/.agent/`)*
3. Your AI IDE / Assistant will automatically detect `.agent/skills/unreal-cpp-developer/SKILL.md` and enforce these guidelines whenever you ask it to work with your C++ files.
4. *(Optional)* Open `custom_rules.md` and add your project-specific rules.

---

## 🤝 Contributing

You are welcome to submit refinements as best-practices natively evolve in future versions of Unreal. Pull requests should follow the formatting style seen in the document, keeping instructions highly condensed and unambiguous!

## 📜 License
MIT License. Feel free to adopt and adjust these instructions freely for commercial or indie ventures alike.
