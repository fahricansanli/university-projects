import os
import pwd
import sys
import re
import datetime
import argparse
import filecmp
from collections import deque

# edits argument inputs for convenience
def correct_argument_inputs():

    if (args.before and len(args.before) < 15):
        args.before += "T999999"

    if (args.after and len(args.after) < 15):
        args.after += "T000000"

    if (args.bigger and args.bigger[-1] == 'K'):
        args.bigger = int(args.bigger[:-1]) * 2**10
    elif (args.bigger and args.bigger[-1] == 'M'):
        args.bigger = int(args.bigger[:-1]) * 2**20
    elif (args.bigger and args.bigger[-1] == 'G'):
        args.bigger = int(args.bigger[:-1]) * 2**30
    elif (args.bigger):
        args.bigger = int(args.bigger)

    if (args.smaller and args.smaller[-1] == 'K'):
        args.smaller = int(args.smaller[:-1]) * 2**10
    elif (args.smaller and args.smaller[-1] == 'M'):
        args.smaller = int(args.smaller[:-1]) * 2**20
    elif (args.smaller and args.smaller[-1] == 'G'):
        args.smaller = int(args.smaller[:-1]) * 2**30
    elif (args.smaller):
        args.smaller = int(args.smaller)

# creates a parser which accepts options: before, after, match, bigger, smaller, delete, zip, duplcont, duplcont, stats, nofilelist, and a directory list
def parse_arguments():

    parser = argparse.ArgumentParser()
    parser.add_argument('-before', dest="before", action='store')
    parser.add_argument('-after', dest="after", action='store')
    parser.add_argument('-match', dest="match", action='store', type=str)
    parser.add_argument('-bigger', dest="bigger", action='store')
    parser.add_argument('-smaller', dest="smaller", action='store')
    parser.add_argument('-delete', dest="delete", action='store_true', default=False)
    parser.add_argument('-zip', dest="zip", action='store', type=str)
    parser.add_argument('-duplcont', dest="duplcont", action='store_true', default=False)
    parser.add_argument('-duplname', dest="duplname", action='store_true', default=False)
    parser.add_argument('-stats', dest="stats", action='store_true', default=False)
    parser.add_argument('-nofilelist', dest="nofilelist", action='store_true', default=False)
    parser.add_argument('dirs', action='store', nargs='*')

    return parser.parse_args()

# returns whether the file’s last modification time is older than the given time
def before(file):
    modtime = os.path.getmtime(file)
    modtime = datetime.datetime.fromtimestamp(modtime).strftime('%Y%m%dT%H%M%S')

    for i in range(15):
        if(args.before[i] != modtime[i]):
            return modtime[i] < args.before[i]
# returns whether the file’s last modification time is newer than the given time
def after(file):
    modtime = os.path.getmtime(file)
    modtime = datetime.datetime.fromtimestamp(modtime).strftime('%Y%m%dT%H%M%S')

    for i in range(15):
        if (args.after[i] != modtime[i]):
            return modtime[i] > args.after[i]

# returns true if the size of file is greater than the given size, false otherwise
def bigger(file):
    filesize = os.path.getsize(file)
    return filesize > args.bigger

# returns true if the size of file is less than the given size, false otherwise
def smaller(file):
    filesize = os.path.getsize(file)
    return filesize < args.smaller

# checks whether name matches with given regular expression
def match(name):
    return bool(re.match(args.match, name))

# deletes the file by running a bash command
def delete(file):
    os.system('rm ' + file)

# zips the files that satisfies the conditions
def zip():

    command = 'mkdir __files_to_be_zipped'
    os.system(command)

    zip_command = 'zip -j ' + args.zip

    for element in names:
        for i in range(len(element)):
            name = element[i][0]
            if(i > 0):
                name += '\(' + str(i) + '\)'

            command = 'cp ' + element[i][1] + ' __files_to_be_zipped/' + name
            zip_command += ' __files_to_be_zipped/' + name
            os.system(command)

    os.system(zip_command)
    os.system('rm -r __files_to_be_zipped')

# argparser
args = parse_arguments()
correct_argument_inputs()

# list of files that satisfies the given conditions
valid_files = []

# change the names of directories with their absolute paths
for i in range(len(args.dirs)):
	args.dirs[i] = os.path.abspath(args.dirs[i])

# deque to traverse directories in bfs order
qlist = deque(args.dirs)
# if no directory is given
if(not qlist):
    qlist.append(os.getcwd())

files_visited = 0
filesize_visited = 0
files_listed = 0
filesize_listed = 0

# a list that contains lists that contain the files with the same names and their paths as a tuple
names = []
# a list that contains lists that contain the files with the same content and their paths as a tuple
contents = []

while(qlist):
    currentdir = qlist.popleft()
    dircontents = os.listdir(currentdir)

    for name in dircontents:
        currentitem = currentdir + '/' + name

        if(os.path.isdir(currentitem)):
            qlist.append(currentitem)
        else:
            files_visited += 1
            filesize_visited += os.path.getsize(currentitem)

            if(args.before and not before(currentitem)):
                continue
            if(args.after and not after(currentitem)):
                continue
            if(args.bigger and not bigger(currentitem)):
                continue
            if(args.smaller and not smaller(currentitem)):
                continue
            if(args.match and not match(name)):
                continue

            files_listed += 1
            filesize_listed += os.path.getsize(currentitem)

            valid_files.append(currentitem)

            if(args.zip or args.duplname):
                flag = False

                for element in names:
                    if(element[0][0] == name):
                        element.append((name, currentitem))
                        flag = True

                if(not flag):
                    names.append([(name, currentitem)])

            if(args.duplcont):
                flag = False

                for element in contents:
                    if(filecmp.cmp(currentitem, element[0][1])):
                        element.append((name, currentitem))
                        flag = True

                if(not flag):
                    contents.append([(name, currentitem)])

# sorts the lists contents and names in lexicographical order  
for i in range(len(contents)):
    contents[i] = sorted(contents[i], key=lambda file: file[0])
contents = sorted(contents, key=lambda element: element[0][0])
names = sorted(names, key=lambda element: element[0][0])

if(not args.nofilelist and args.duplname):
    for element in names:
        print('------')
        for i in element:
            print(i[1])
    print('------')

if(not args.nofilelist and args.duplcont):
    for element in contents:
        print('------')
        for i in element:
            print(i[1])
    print('------')

if(args.zip):
    zip()

# if no other output options is given, print the files visited
if(not args.duplcont and not args.duplname and not args.nofilelist):
    for file in valid_files:
        print(file)

if(args.stats):
    print(files_visited)
    print(filesize_visited)
    print(files_listed)
    print(filesize_listed)

    if(args.duplname):
        print(len(names))

    if(args.duplcont):
        print(len(contents))

        total_size = 0
        for i in contents:
            total_size += os.path.getsize(i[0][1])

        print(total_size)

if(args.delete):
    for file in valid_files:
        delete(file)