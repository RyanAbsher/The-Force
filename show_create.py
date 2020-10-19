# This program reads in show definitions from def.txt and outputs def.h to  be used by the Arduino program

# startTime set channel value
# startTime fade channel startValue endValue
# startTime blink channel blinkNumber blinkDuration gapDuration
import operator
commands = []
definitions = open("def.txt", "r")
data = definitions.readlines()
definitions.close()
for line in data:
    tokens = line.split()
    if(tokens[0] == "#"):
       continue
    elif(tokens[1] == "set"):
        command = [tokens[2], tokens[3], int(tokens[0]) * 10]
        commands.append(command)
    elif(tokens[1] == "fade"):
        if(int(tokens[4]) > int(tokens[3])): # If we are fading up
            value = int(tokens[3])
            step = 0
            while(value < int(tokens[4])):
                command = [tokens[2], value, ((int(tokens[0]) * 10) + (1*step))]
                commands.append(command)
                value = value + 20
                if(value > 255):
                    value = 255
                step = step + 1
        else: # if we are fading down
            value = int(tokens[3])
            step = 0
            while(value >= int(tokens[4])):
                command = [tokens[2], value, ((int(tokens[0]) * 10) + (1*step))]
                commands.append(command)
                value = value - 20
                if(value == -20):
                    value == -1
                    continue
                elif(value < 0):
                    value = 0
                step = step + 1
    elif(tokens[1] == "blink"):
        blink = 0
        while(blink < (int(tokens[3]))*2):
            command = [tokens[2], 255, ((int(tokens[0]) * 10) + (1*blink))]
            blink = blink + 1
            commands.append(command)
            command = [tokens[2], 0, ((int(tokens[0]) * 10) + (1*blink))]
            commands.append(command)
            blink = blink + 1

#Sort Everything
commands = sorted(commands, key=operator.itemgetter(2))


outFile = open("def.h", "w")
outFile.write("#define NUM_DEF ")
outFile.write(str(len(commands)-1))
outFile.write("\n")

line1 = "const byte fixtureNumber[" + str(len(commands)) + "]= {"
line2 = "const byte sendValue[" + str(len(commands)) + "]= {"
line3 = "const int startTime[" + str(len(commands)) + "]= {"

for item in commands:
    if(not item == commands[len(commands)-1]):
       line1 = line1 + item[0] + ", "
       line2 = line2 + str(item[1]) + ", "
       line3 = line3 + str(item[2]) + ", "
    else:
        line1 = line1 + item[0] + "};\n"
        line2 = line2 + str(item[1]) + "};\n"
        line3 = line3 + str(item[2]) + "};\n"
outFile.write(line1)
outFile.write(line2)
outFile.write(line3)

outFile.close()
              
    

