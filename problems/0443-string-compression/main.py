from typing import List

class Solution:
    def compress(self, chars: List[str]) -> int:
        # ! Reference solution for C++
        # ! def get_num_digits(num):
        # !     if num < 10: return 1
        # !     if num < 100: return 2
        # !     if num < 1000: return 3
        # !     return 4
 
        # ! def write_curr_char():
        # !     nonlocal write_pos, count
        # !     chars[write_pos] = curr_char
        # !     write_pos += 1

        # !     if count == 1:
        # !         return 
        # !     num_digits = get_num_digits(count)
        # !     j = write_pos + num_digits - 1
        # !     while count:
        # !         chars[j] = str(count % 10)
        # !         count = count // 10
        # !         j -= 1
          
        # !     write_pos += num_digits


        def write_curr_char():
            nonlocal write_pos, count
            chars[write_pos] = curr_char
            write_pos += 1

            if count == 1:
                return
            
            for c in str(count):
                chars[write_pos] = c
                write_pos += 1


        n = len(chars)
        curr_char = chars[0]
        count = 1

        write_pos = 0
        read_pos = 1
        while (read_pos < n):
            if chars[read_pos] == curr_char:
                count += 1
                read_pos += 1
                continue

            write_curr_char()
            curr_char = chars[read_pos]
            count = 1
            read_pos += 1


        write_curr_char()
        return write_pos

            