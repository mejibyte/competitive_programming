# @param {String} s
# @return {Integer}
def length_of_longest_substring(s)
    best = 0
    i = 0
    seen = {}
    seen.default = 0
    # Possible solution is s[i, j)
    s.each_char.each_with_index do |_, j|
        while seen[s[j]] > 0 and i < j
            seen[s[i]] = seen[s[i]] - 1
            i += 1
        end
        seen[s[j]] += 1
        best = [best, j - i + 1].max
    end
    return best
end
