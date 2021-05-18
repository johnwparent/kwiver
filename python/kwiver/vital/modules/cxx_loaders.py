import ctypes
import os, platform


def PyLoadLibrary(lib):
    plt = platform.system()
    if plt == "Windows":
        from ctypes import windll as loader
    elif plt == "Linux" or plt == "Darwin":
        from ctypes import cdll as loader
    else:
        raise RuntimeError("Cannot determine host system")

    return loader.LoadLibrary(lib)

