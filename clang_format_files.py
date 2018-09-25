import subprocess
import os
import argparse
import sys
import glob

def log(message):
    nameOfThisScript = sys.argv[0]
    print('[{}] {}'.format(nameOfThisScript, message))

def get_file_extension(filename):
    extension = ''
    try:
        extension = filename.split('.')[-1]
    except:
        pass
    return extension

def get_extensions_to_format():
    return ['cpp', 'h']

def is_needed_to_format(filename):
    extensionsToFormat = get_extensions_to_format()
    return get_file_extension(filename) in extensionsToFormat

def get_staged_files(gitRootDirectory):
    fileNames = subprocess.check_output("cd {};git ls-tree -r master --name-only".format(gitRootDirectory), shell=True).decode().split()
    return [os.path.join(gitRootDirectory, f) for f in fileNames]

def clang_format_files(fileNames, isSilent):
    for _file in fileNames:
        _file = _file.replace('\\', '/')
        if is_needed_to_format(_file):
            command = 'clang-format-6.0 -i -style=file {}'.format(_file)
            if isSilent:
                log(command)
            else:
                subprocess.call(command, shell=True)

def get_file_names_recursively(rootDir):
    if not os.path.exists(os.path.dirname(rootDir)):
        raise NotADirectoryError('{} is not a valid directory.'.format(rootDir))

    files = []
    for _ext in get_extensions_to_format():
        files.extend(glob.glob(os.path.join(rootDir, '*.{}'.format(_ext))))

    return files

def get_files_to_format(dirName, isRecursive):
    if not os.path.exists(os.path.dirname(dirName)):
        raise NotADirectoryError('{} is not a valid directory.'.format(dirName))

    if isRecursive:
        return get_file_names_recursively(dirName)
    else:
        return get_staged_files(dirName)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Clang format runner script.')
    parser.add_argument('dir', help='directory where clang-formatting has to be applied.')
    parser.add_argument('--silent', help='Don\'t format, just log the files to be formatted.', action='store_true')
    parser.add_argument('--recursive', help='Instead of getting the staged files, search for all files recursively.', action='store_true')
    #parser.add_argument('--run', help='Run without cmake update and build.', action='store_true')

    args = parser.parse_args()
    args.dir = os.path.abspath(args.dir)

    clang_format_files(get_files_to_format(args.dir, args.recursive), args.silent)
