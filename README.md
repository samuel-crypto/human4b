# human4b
**human4b** is a humanly computable stream cipher, with a round design that is simple enough for most people to master (notably one has to mostly keep no more than 3 numbers in your head during a round).

## How to test/use

Because this is not currently designed for practical use, but for cryptoanalysis, scrutiny and criticism, the less practical but more cryptoanalytically useful side of generating a keystream is revealed (if the keystream is strong there is no need for any other proof of strength).

### How to generate a keystream

First compile the program by running `make human4b`.
Next, run the following command:

`./human4b --hex 1`

Which should generate the following keystream:

`A6215D8D15102C25797961C439ECFC221E41B33D12520CC6C8E550418A241DBD6E82F756C461E61ADF8AA298CF40A96B7AE61D271E9DCA1E70C5F90AAB55AF9A8020E0254BAD496D245E67D1B74BDB74BFBE425B21212619E62B1BD0DD3EA00D3A5CB5D74C4766C906D61636D8558CC15E3000901FDB0FD074C689452FD1C170`

### Extra options / supplying an actual key

In place of the `--hex` I used above you can also use `--bin` which will simply print the binary characters equivalent to two keystream outputs (e.g. `01` will become one `1` byte).

The key (or seed) is in hex format (e.g. `FFFF` is a valid key) and **HAS** to be of length `3N + 1` where `N` is a natural number. This length is by design (to allow all pieces of the key to be added to the output stream). The other restriction is that the first key character cannot be `0`, the reason for this is that the cipher does not have any magic numbers, and there is simply no way to get from 0 to anything else for the first output character (the other characters of such a stream are fine, but the fact that the first one will always be `0` is obviously a vulnerability, which is why keys beginning with `0` are considered weak keys and should not be used).

### Test vectors (to make sure everything worked)
Running `./human4b --hex 1000000000000` gives output:

`A81C790E3EA5284A760ED287970043DC8222EE495D24B2241E4AED7D8843B885D51DA028DE8819E6E69D558140D0CB2208DDB80482508E999FD822B8D3A4A61D59FBA82E2840424E06C48262435F489E2205AEF94286C2D84701FF073219C277D55EDAB313428DDD4878670DAEA484E39278DC1E6D7FD5280EAF2A42D5ADE3E0`

Running `./human4b --hex 1000000000001` gives output:

`DC2BADA07053FC2EA0A2A2E26478270CC93D0032A04894D2536F21A5286A1C8A0F5A5A380FCC5B04026053C5DA045924AC05187DE4FAC3DDF70C351E4C585D555F21E820DC6A6920E25EC4096C392C6093A35076D3C0BD1C8AA2997D792D5D2409FF5D1727E5CA00284C4DA2E0DD23A7624CA5200529A39EA0579D22AA500CF0`

Running `./human4b --hex FFFF0000FFFF0000FFFF0000F` gives output:

`DA9F2E09D91E5041D89C05C2ACA3C3A04A939313A689A93C95C1859910CEBD52A9975B0905028549D805882B59DD65148F84DCACB304135A94D9EC98B25973341370098FAF3139939AE33D55C48D8379D8759D06699E9CA5599989CA90427150CD034A66394A2942D39A5F54938535399A299A2114135ACB7C1ADABAF448B210
`

## For analysis
### Round design diagram

The round design digram I have created (in probably pretty readable form), and it can be seen [here](https://www.draw.io/?lightbox=1&highlight=0000ff&edit=_blank&layers=1&nav=1&title=Untitled%20Diagram.xml#R5VtNk6M2EP01PmYLIQns49g7m01VUpvKHDJ7ZG2NTRYjIouxnV8fYcSnxKxTNg1D5jAFjayPp9cPdUvM8Gp%2F%2BlkEye43vmHRzHU2pxn%2BOHPdue%2Bp%2F5nhnBsIcnPDVoSb3IQqw1P4D9NGR1vTcMMOjYKS80iGSdO45nHM1rJhC4Tgx2axFx41W02CLTMMT%2BsgMq1%2Fhhu508Ny%2Fcr%2BmYXbXdEy8hb5k2%2FB%2BvtW8DTW7c1c%2FHL5yx%2Fvg6IuPdDDLtjwY82EH2d4JTiX%2BdX%2BtGJRBm0BW%2F67Tx1Py34LFstrfqCn5TWIUj30z%2Bk%2BiMlSGVdhsmNCXeTjUTCm8VqGPNZdl%2BcCLslOqrXlTu4jZUDq8iAF%2F85WPOJCWWIeq5LLlzCKWqYgCrexul2r%2Fqq28PKVCRmqiXjQD%2FbhZpM1szzuQsmekmCdtXlUrFO2S8dYNhRH3emhqArYqRMOVIKsuMv4nklxVkUK4uppKWirb48VB2gxc7va%2FBe2QNNuW1ZcQa8uNPodU4cMWNlGkVLfciF3fMvjIHqsrC0AavizUyifM%2FMHqu%2B%2BFk9i1bHao%2Bz2q67gLyblWXtjkEquTFW7v3Ke6DrynmbdextnNRqeirUuhbUjB2LLdCnPPhuCRYEMX5u13wSuDwMuOIDoVgT1T3%2FnoWq49APacoRSmIsq8j7oX1Xz8CBEcK4VS7ICh%2B52UEc7nzrKE3JbeYJoizZ5jysSlRhexStsyOcvcZLKGV0%2Bz%2BhHg3NNRtkUrcayO8gZcpvDX5h6hmx65t1Dz1xgPUMNNbuU69cdyYB6RqagZxYAEQZCkLzhuZlLZAsgNAYfxs6APkyn7sN0QAqi%2BRSc2IYglAzSK5zYHYMTk%2FlwTlwsUqYbWHgmBfPAFoCCnkHBmetFWTT8TV1ss4vnL38UNlVbaTZnJYrC5NAV6955ZUhpg5Al0%2BqhroWQ9B6EhH6rgBMSWSK1fMUB8Voxg5J3QUmMm5TEGJCSQPmBASlpE0mwcOWdqiRFLUpa3tt9UbJg%2F3Qp6boWSs6BKInBPR46tLHBi%2B%2BSLrw1y0fpD7J2%2BLby%2FsJpUeG2LF%2BBZFO%2Bgn0mOFqk3rpzzMw%2BeCKQNIWM%2BKaQ%2BRYhu8fGBobe2ABPItgSWXBCBpQKHPA9YYEXQ8V3lkThf%2FJ9M%2FgGTyC6A%2Fr%2B5BOItuQDGDkxUAZxQN%2B3wQsVttiTO9f7vju471NnON8nQAFMzwScWwi4gCLg3EbAS4z8wi8r4Apc7%2B%2BUFw9%2BOlzgeFAFCEpO1cMqql7Wgu28ro54G36p6n9okpZaom6PmqS9R7KcAL2wej4oYgn9CNS2VtH4%2F4m02G2T1rMobW%2BkncRGIra86okPRdruDOVkSUudNml9yy5QX6Sl5uroPZJ2YZKWdsB%2Bf9IuOkk76rR6e%2FNx4cCl1UkvtEM10tVipEHyvqQ4MD%2FEirVofPxHMlAzZzxfUIODvR3JoJPP2RHLDjgFO9s3kR1wUF30eqFkty7CH9e1pJHBgiJyzXlTPAZdJAi3VoWw0tgPD8ckjb5FGikUD%2F33KY1e63UNKY20n0TmmKTREsWAhd7EjGJMaSRjkEZvPuSa0VxZf0llhlP2fatQ%2F%2BPsK8zya82hl9etT4%2BQY%2FmYsj%2BwzBXgmMFqf%2BMBDJZ5jH7MYFGfwoGlbquPsfOjQ9UH7%2FjxXw%3D%3D). All calculations work with 4-bit numbers. The other thing is I tried making the round function in the code readable, so if you prefer that feel free.

### Reasoning about security

I do not personally think this will turn out to be a strong PRNG, while the output (and diffusion) appears to be impressive at first sight, I can already find suspicious repeats, and some keys that appear to be weak, for example:

`[samuel@localhost HumanC]$ ./human4b --hex 1000000004
6274730FD968329174EDBE49A5C39D6CCFDAFAB11163F6A99E80D4731D38AAD1659D60ED1ACC94A493A168A9BE6D8FE6E263ADCB165EA63FC41CE0A1FC6366936C5A1$
[samuel@localhost HumanC]$ ./human4b --hex 1000000005
016F4CA40BE2B1C54BA24A1CCCBDC0D7185D4B8F33D5BDDCE2ED2946A962C293D8E0EA393D11EFB4B9C3422EAAD77BADA1D6C9BADD8A21C1523136CDE5E5E7E6453C5$
[samuel@localhost HumanC]$ ./human4b --hex 1000000006
BCE0EF5208AFDCB1EE98E6BAC522B03F85B62C13C565466BDA7A8EEFE61A4B6C3FD0A5B65788DCCB80C5DFBD393214669C3F462316F9B2F20358B64101A5AFDFD0941$
[samuel@localhost HumanC]$ ./human4b --hex 1000000005
016F4CA40BE2B1C54BA24A1CCCBDC0D7185D4B8F33D5BDDCE2ED2946A962C293D8E0EA393D11EFB4B9C3422EAAD77BADA1D6C9BADD8A21C1523136CDE5E5E7E6453C5$`

One will notice that 'CC' then '11' then '88' and '11' appear to repeat in the same position in all the keystreams.
The other concern is that the keystream has a maximum length of 256, but if this is close to a CSPRNG one can simply use the first 3 chars of the key as a nonce (which requires uniqueness but not randomness), which would hugely increase the number of encryptable messages.

Another suspicion I have is that a large source of defects comes from increasing the key length while keeping monotonous values, while a key of `0`s is impractical (one would want a random key), I am ready to consider efficient any attacks, including those against `0` padded keys.

### Design ideas

The 3 operations `+`, `xor` and `>>>` (right rotate) were chosen because addition is easy to compute modulo 16 for humans, xor can be aided by the use of a table for beginners (without revealing the state of calculation), and rotation can be treated as an S-box (which also can be written on a piece of paper without compromising security). The constant rotates in the middle of the round are designed to 'offset' the bitstring from each other, in an attempt to make the output less linear (using actual S-boxes, such as 4-bit optimal S-boxes, proved risky, because it appears to be very difficult to design a good S-box which will not result in some weird pattern / loop in such a construction - especially for 4 bits).

The main design was allowing a human to work with at most (around) 3 numbers at any given time (not including the key, which would be memorized), allowing a trained human to perform calculations in his/her head. To compensate for this, there is a large number of rounds involved to introduce more security.

### Posting attacks / reporting issues

If you found some kind of attack (even marginally efficient compared to pure brute-force), feel free to reply on reddit (if it is catastrophical) or raise an issue here. I created this because I couldn't find anything like this before, and I don't expect attempt #1 to be strong, not only that I myself have found some iffy points that I suspect will turn into (even perhaps practical) attacks, which some of you will no doubt find.

