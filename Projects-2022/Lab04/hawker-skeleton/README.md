# Hawker
[![Build Status](https://travis-ci.com/khale/hawker.svg?token=576AGsdiqBgiBzCbaoJT&branch=master)](https://travis-ci.com/khale/hawker)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

Hawker is a small container engine designed to teach students the
concepts behind containers. It implements a reasonable subset of 
functionality that one might find in Docker or LXC such that
students get an idea of how the machinery underlying containers work.

Note that Hawker is Linux-specific.

## Table of Contents

- [Background](#background)
- [Install](#install)
- [Usage](#usage)
- [Maintainers](#maintainers)
- [Contributing](#contributing)
- [License](#license)


## Background
This program was originally created in the Fall of 2018 to serve as a student project
for the creator's class on virtual machines at Illinois Institute of Technology. The goal
here was to provide enough of a playground in C for students to get a feel for how
commodity tools like LXC and Docker work


## Installation
You simply must run the setup script:

    sudo ./setup.sh

Note that this script will ask for your sudo password.


## Usage
Hawker must be run as root so that it can use `mknod()` when creating
containers. The author claims that this is not unreasonable as even with
Docker, the Docker daemon is running as root (your user must be added to
a privileged group to use the client). For example, to run a shell within
a test image:

    sudo ./hawker test sh

## Maintainers
Hawker is currently maintained by Kyle C. Hale <khale@cs.iit.edu>

## Contributing
TBD


## License
[MIT](LICENSE)
