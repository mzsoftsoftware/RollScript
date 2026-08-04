## Printer Handling

RollScript supports one active printer connection in the normal
interactive workflow.

The PrinterManager manages exactly one current PrinterInstance.
PrinterPlugins may therefore keep a reference to the active
PrinterInstance while the printer is open.

Multiple simultaneously opened printers are not supported by the
standard print workflow.

Features requiring multiple printers (for example batch printing)
must implement their own printer lifecycle management.
