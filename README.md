# C++ Web Crawler

A simple web crawler written in C++ using WinINet for HTTP requests.

## How It Works

1. **Start**: Begins crawling from a given URL
2. **Download**: Fetches the HTML content of the page
3. **Parse**: Extracts all links from `<a href="...">` tags
4. **Normalize**: Converts relative URLs (e.g., `/about`) to absolute URLs
5. **Filter**: Only follows links from the same domain
6. **Recurse**: Repeats the process for each found link up to max depth
7. **Track**: Keeps a set of visited URLs to avoid crawling the same page twice

### Max Depth

The max depth parameter controls how deep the crawler goes:
- **Depth 0**: Only the starting URL
- **Depth 1**: Starting URL + all links found on it
- **Depth 2**: Starting URL + its links + links found on those pages
- And so on...


