#!/usr/bin/env python3

import argparse

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("filename", help="bin file with dump")
    args = parser.parse_args()

if __name__ == "__main__":
    main()
