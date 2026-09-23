#!/usr/bin/env python3
"""Validate inline SVGs embedded in a Markdown document.

Usage:
    python3 validate_svgs.py <file.md>

Checks:
  * every <svg>...</svg> block is well-formed XML
  * no <svg> is wrapped in a fenced code block (it would not render)
  * <marker> ids are unique across the document
  * reports each SVG's viewBox and length

Exit code 0 when all checks pass, 1 on any error.
"""

import re
import sys
import xml.etree.ElementTree as ET


def main(path: str) -> int:
    with open(path, encoding="utf-8") as fh:
        text = fh.read()

    ok = True
    svgs = re.findall(r"<svg\b.*?</svg>", text, re.S)
    if not svgs:
        print(f"no <svg> found in {path}")
        return 1

    for i, svg in enumerate(svgs):
        try:
            root = ET.fromstring(svg)
            print(f"[{i}] OK  viewBox={root.get('viewBox', '?')}  len={len(svg)}")
        except ET.ParseError as exc:
            ok = False
            print(f"[{i}] XML ERROR: {exc}")

    for match in re.finditer(r"```.*?```", text, re.S):
        if "<svg" in match.group(0):
            ok = False
            print(f"ERROR: <svg> inside a fenced code block at offset {match.start()}")

    ids = re.findall(r'<marker id="([^"]+)"', text)
    duplicates = sorted({x for x in ids if ids.count(x) > 1})
    if duplicates:
        ok = False
        print(f"ERROR: duplicate marker ids: {duplicates}")

    print(f"SVG count: {len(svgs)} | marker ids: {len(ids)} | unique: {len(set(ids))}")
    return 0 if ok else 1


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print(__doc__)
        sys.exit(2)
    sys.exit(main(sys.argv[1]))
