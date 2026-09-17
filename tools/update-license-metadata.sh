#!/bin/bash

set -e

# -----------------------------------------------------------------------------
# update-license-metadata.sh
#
# Retrieves license information for a GitHub repository and writes it
# to a local JSON metadata file.
#
# Usage:
#   ./update-license-metadata.sh <github-repository> <output-file>
#
# Example:
#   ./update-license-metadata.sh \
#       libusb/libusb-cmake \
#       build/.../Resources/Licenses/libusb-license.json
# -----------------------------------------------------------------------------

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <github-repository> <output-file>"
    echo
    echo "Example:"
    echo "  $0 libusb/libusb-cmake build/.../libusb-license.json"
    exit 1
fi

REPOSITORY="$1"
OUTPUT_FILE="$2"

API_URL="https://api.github.com/repos/${REPOSITORY}"
LICENSE_API_URL="https://api.github.com/repos/${REPOSITORY}/license"

# -----------------------------------------------------------------------------
# Retrieve license information from GitHub
# -----------------------------------------------------------------------------

REPOSITORY_JSON=$(curl -fsSL "$API_URL")
LICENSE_JSON=$(curl -fsSL "$LICENSE_API_URL")

# -----------------------------------------------------------------------------
# Extract relevant information
# -----------------------------------------------------------------------------

python3 - "$OUTPUT_FILE" "$REPOSITORY" "$REPOSITORY_JSON" "$LICENSE_JSON" <<'PY'
import json
import sys

output_file = sys.argv[1]
repository = sys.argv[2]
repository_json = sys.argv[3]
license_json = sys.argv[4]

repository_data = json.loads(repository_json)
license_data = json.loads(license_json)

name = repository_data.get("name")
license_info = license_data.get("license") or {}

spdx_id = license_info.get("spdx_id")

if not spdx_id:
    raise SystemExit(
        "GitHub did not provide an SPDX license identifier"
    )

if not name:
    raise SystemExit(
        "GitHub did not provide a license name"
    )

metadata = {
    "repository": repository,
    "spdx_id": spdx_id,
    "name": name
}

with open(output_file, "w", encoding="utf-8") as file:
    json.dump(
        metadata,
        file,
        indent=4,
        ensure_ascii=False
    )
    file.write("\n")
PY

echo "License metadata written to:"
echo "$OUTPUT_FILE"
echo "Repository: $REPOSITORY"
echo "SPDX:       $(python3 -c "import json; print(json.load(open('$OUTPUT_FILE'))['spdx_id'])")"

