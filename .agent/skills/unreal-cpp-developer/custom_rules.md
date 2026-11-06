# Project-specific rules

Read existing entries in this installed copy as legacy project-specific overrides within their original scope. Explicit user instructions and repository engineering instructions remain authoritative. During [project setup](references/project-setup.md), ask in the user's language whether to define additional team rules now or later. Keep core workflow choices in the project's active instructions. Save agreed additions in the project's own `custom_rules.md` or existing team guide and link to it from those instructions.

No project-specific rules are enabled in this distributed file. If a shared installation contains rules from an earlier project, establish their scope before applying or importing them into another repository.

Useful topics for your own rules include:

- Folder layout for source code and content, C++ coding conventions, asset names and any other team requirements.
- Required authoring access through Details, Blueprint, and Sequencer.
- Public naming, compatibility, and serialization requirements.
- Component autonomy, allowed dependencies, and module boundaries.
- Project-specific logging, formatting, and lifecycle contracts.
- Permitted validation commands and release/versioning conventions.

State requirements directly. Examples are not automatically requirements. Prefer referencing an existing authoritative project document over maintaining competing copies.

The base skill permits only Editor tooltip comments in final generated code. Instructional comments inside the supplied templates are guidance for the agent and must not be copied into final implementations.
