class Tag:
    def __init__(self, position=0, length=0,next_char=''):
        self.position = position
        self.length = length
        self.next_char = next_char

    def __str__(self):
        return f"<{self.position},{self.length},{self.next_char}>"

 

def LZ77_Compress(Text):
    Tags = []

    searchWindow_begin = -8
    searchWindow_end = 0
    lookAhead_end = 8

    while searchWindow_end < len(Text):
        pos = 0
        length = 0
        next_ch = ''
        
        for i in range(searchWindow_end,lookAhead_end):
            if i > len(Text)-1:
                break
            k = i
            for j in reversed(range(searchWindow_begin,searchWindow_end)):
                if j < 0:
                    next_ch = Text[i]
                    break

                if Text[k] == Text[j]:
                    k -=1
                elif Text[i] == Text[j]:
                    k = i -1
                else:
                    k = i
            
                if k < searchWindow_end:
                    pos = searchWindow_end - j
                    length = i - k
                    if i+1 < len(Text):
                        next_ch = Text[i+1]
                    break

            if k >= searchWindow_end:
                break


        Tags.append(Tag(pos, length, next_ch))
        searchWindow_begin += length+1
        searchWindow_end += length+1
        lookAhead_end += length+1
                
        
    return Tags 



def LZ77_Decompress(Tags):
    text = ""
    for tag in Tags:
        i = j = len(text)-tag.position
        while i < tag.length+j:
            text+= text[i]
            i += 1
        text += tag.next_char
    return text
        



# Text = "FFFFFFFFFFFFFFFFFFFFFFFFFFFFF"
Text = "ABAABABAABBBBBBBBBBBBA"


Compressed = LZ77_Compress(Text)

for tag in Compressed:
    print(tag)

Decompressed = LZ77_Decompress(Compressed)

print(Decompressed)
