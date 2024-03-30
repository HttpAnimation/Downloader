#!/bin/bash

# Check if pages.txt exists
if [ ! -f "pages.txt" ]; then
    echo "pages.txt not found!"
    exit 1
fi

# Check if a download path is provided
if [ $# -eq 0 ]; then
    echo "Usage: $0 <download_path>"
    exit 1
fi

download_path="$1"

# Ensure download path exists
if [ ! -d "$download_path" ]; then
    echo "Download path $download_path does not exist!"
    exit 1
fi

# Iterate over each URL in pages.txt
while IFS= read -r url; do
    echo "Downloading $url ..."
    curl -o "$download_path/$(basename $url)" "$url"
    echo "Download of $url complete."
done < "pages.txt"

echo "All downloads complete."
