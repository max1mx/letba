
Legba is a multiprotocol credentials bruteforcer / password sprayer and enumerator built with Rust and the Tokio asynchronous runtime in order to achieve
[better performances and stability](https://legba.evilsocket.net/benchmark/) while consuming less resources than similar tools.

## Key Features

- **100% Rust** - Legba is entirely written in Rust, does not have native dependencies and can be easily compiled for all operating systems and architectures. 🦀
- **Multi Protocol** - Support for HTTP, DNS, SSH, FTP, SMTP, RDP, VNC, SQL databases, NoSQL, LDAP, Kerberos, SAMBA, SNMP, STOMP, MQTT [and more](https://legba.evilsocket.net/).
- **High Performance** - Async/concurrent architecture with customizable workers for [maximum speed](https://legba.evilsocket.net/benchmark/).
- **Flexible Credentials** - [Multiple input formats](https://legba.evilsocket.net/usage/) including wordlist files, ranges, permutations, and expression generators.
- **Smart Session Management** - Save and restore session state to resume interrupted scans.
- **Advanced Rate Control** - Rate limiting, delays, jittering, and retry mechanisms for stealth and stability.
- **AI Ready** - [REST API](https://legba.evilsocket.net/rest/), [Model Context Protocol (MCP)](https://legba.evilsocket.net/mcp/) server, and custom binary plugin support.
- **Recipe System** - [YAML-based configuration](https://legba.evilsocket.net/recipes/) for complex authentication scenarios.
- **Multiple Output Formats** - Export results in various formats for easy integration with other tools.

## Quick Start

Download one of the precompiled binaries from the [project latest release page](https://github.com/evilsocket/legba/releases/latest), or if you're a **Homebrew** user, you can install it with a custom tap:

```bash
brew tap evilsocket/legba https://github.com/evilsocket/legba
brew install evilsocket/legba/legba
```

You are now ready to go! 🚀

```bash
legba smb --target domain.local --username administrator --password wordlist.txt
```

For the usage and the complete list of options [check the project documentation](https://legba.evilsocket.net/).

### AI Agent Skill

If you use an AI coding agent (Claude Code, Cursor, Copilot, OpenCode, etc.), you can install the legba skill to give it full knowledge of the tool — syntax, plugins, recipes, and API:

```bash
npx skills add https://github.com/evilsocket/legba --skill legba
```

Once installed, your agent will know how to construct legba commands, write recipes, and configure the REST API or MCP server without needing to look things up manually.
