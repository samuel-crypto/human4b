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

`A92A946338EBC3B78CF0B62D1F847E060A585BEA6CA67AB407108CC17141B4486F5F426D6929FDCA97B13B3BD4FE7FA15B6FC05BA601A59DC72E836330F62BC4D8276DFDA0ED2F242BC81B17614F1F290CD0996F04CF869299ADD7EABED1CF8CD9E3513D92F374A04963751240878B7CA607D08D53AEDBDD725A81A7D287A530`

Running `./human4b --hex 1000000000001` gives output:

`2CC9E7E87EDA0D004404573BBD8E5650DC01C3B7E67681A8695807681C42D95766073F3ECB3533E3EDC7A5FEDFF8601B15DDC511A9E8101404FFCE1C74B916DD4935EB8C073D219DF67654A625C0E6F6A5C78F3E9D81AE24C371D330F648767A088F27B0C676480B2B8B2BC80EE9BEB822467BD22D1F4EFE3CF341578FF5A080`

Running `./human4b --hex FFFF0000FFFF0000FFFF0000F` gives output:

`82813DEEFEBA13C5A5E00E678A56A409A4FF8AF8252BFBEA5505AE57F6DA72E384CA3EBF64012F2847CCDE24C76489E11C953C23B11A26B988DC1729E8D579FAD3B5E06F8A49DECE83F6BF33203BDB8327BA9DD65550854A16B24463A23DAA94B308C70A01BBF402F787F80A25DB5352ADABD3AC2825A5FA1178A0CB1AA4BFB0
`

## For analysis
### Round design diagram

**EDIT: Round design is currently not mirroring what is happening, it will be updated soon, for now please look at the code's round design**

The round design digram I have created (in probably pretty readable form), and it can be seen [here](https://www.draw.io/?lightbox=1&highlight=0000ff&edit=_blank&layers=1&nav=1&title=Untitled%20Diagram.xml#R5VtNk6M2EP01PmYLIQns49g7m01VUpvKHDJ7ZG2NTRYjIouxnV8fYcSnxKxTNg1D5jAFjayPp9cPdUvM8Gp%2F%2BlkEye43vmHRzHU2pxn%2BOHPdue%2Bp%2F5nhnBsIcnPDVoSb3IQqw1P4D9NGR1vTcMMOjYKS80iGSdO45nHM1rJhC4Tgx2axFx41W02CLTMMT%2BsgMq1%2Fhhu508Ny%2Fcr%2BmYXbXdEy8hb5k2%2FB%2BvtW8DTW7c1c%2FHL5yx%2Fvg6IuPdDDLtjwY82EH2d4JTiX%2BdX%2BtGJRBm0BW%2F67Tx1Py34LFstrfqCn5TWIUj30z%2Bk%2BiMlSGVdhsmNCXeTjUTCm8VqGPNZdl%2BcCLslOqrXlTu4jZUDq8iAF%2F85WPOJCWWIeq5LLlzCKWqYgCrexul2r%2Fqq28PKVCRmqiXjQD%2FbhZpM1szzuQsmekmCdtXlUrFO2S8dYNhRH3emhqArYqRMOVIKsuMv4nklxVkUK4uppKWirb48VB2gxc7va%2FBe2QNNuW1ZcQa8uNPodU4cMWNlGkVLfciF3fMvjIHqsrC0AavizUyifM%2FMHqu%2B%2BFk9i1bHao%2Bz2q67gLyblWXtjkEquTFW7v3Ke6DrynmbdextnNRqeirUuhbUjB2LLdCnPPhuCRYEMX5u13wSuDwMuOIDoVgT1T3%2FnoWq49APacoRSmIsq8j7oX1Xz8CBEcK4VS7ICh%2B52UEc7nzrKE3JbeYJoizZ5jysSlRhexStsyOcvcZLKGV0%2Bz%2BhHg3NNRtkUrcayO8gZcpvDX5h6hmx65t1Dz1xgPUMNNbuU69cdyYB6RqagZxYAEQZCkLzhuZlLZAsgNAYfxs6APkyn7sN0QAqi%2BRSc2IYglAzSK5zYHYMTk%2FlwTlwsUqYbWHgmBfPAFoCCnkHBmetFWTT8TV1ss4vnL38UNlVbaTZnJYrC5NAV6955ZUhpg5Al0%2BqhroWQ9B6EhH6rgBMSWSK1fMUB8Voxg5J3QUmMm5TEGJCSQPmBASlpE0mwcOWdqiRFLUpa3tt9UbJg%2F3Qp6boWSs6BKInBPR46tLHBi%2B%2BSLrw1y0fpD7J2%2BLby%2FsJpUeG2LF%2BBZFO%2Bgn0mOFqk3rpzzMw%2BeCKQNIWM%2BKaQ%2BRYhu8fGBobe2ABPItgSWXBCBpQKHPA9YYEXQ8V3lkThf%2FJ9M%2FgGTyC6A%2Fr%2B5BOItuQDGDkxUAZxQN%2B3wQsVttiTO9f7vju471NnON8nQAFMzwScWwi4gCLg3EbAS4z8wi8r4Apc7%2B%2BUFw9%2BOlzgeFAFCEpO1cMqql7Wgu28ro54G36p6n9okpZaom6PmqS9R7KcAL2wej4oYgn9CNS2VtH4%2F4m02G2T1rMobW%2BkncRGIra86okPRdruDOVkSUudNml9yy5QX6Sl5uroPZJ2YZKWdsB%2Bf9IuOkk76rR6e%2FNx4cCl1UkvtEM10tVipEHyvqQ4MD%2FEirVofPxHMlAzZzxfUIODvR3JoJPP2RHLDjgFO9s3kR1wUF30eqFkty7CH9e1pJHBgiJyzXlTPAZdJAi3VoWw0tgPD8ckjb5FGikUD%2F33KY1e63UNKY20n0TmmKTREsWAhd7EjGJMaSRjkEZvPuSa0VxZf0llhlP2fatQ%2F%2BPsK8zya82hl9etT4%2BQY%2FmYsj%2BwzBXgmMFqf%2BMBDJZ5jH7MYFGfwoGlbquPsfOjQ9UH7%2FjxXw%3D%3D). All calculations work with 4-bit numbers. The other thing is I tried making the round function in the code readable, so if you prefer that feel free.

### Reasoning about security

I do not personally think this will turn out to be a strong PRNG, while the output (and diffusion) appears to be impressive at first sight, I can already find suspicious repeats, and some keys that appear to be weak, for example:

Previous suspicious stuff here was just a result of a typo in the code it appears and was not representative of the strength of the stream cipher.

### Design ideas

The 3 operations `+`, `xor` and `>>>` (right rotate) were chosen because addition is easy to compute modulo 16 for humans, xor can be aided by the use of a table for beginners (without revealing the state of calculation), and rotation can be treated as an S-box (which also can be written on a piece of paper without compromising security). The constant rotates in the middle of the round are designed to 'offset' the bitstring from each other, in an attempt to make the output less linear (using actual S-boxes, such as 4-bit optimal S-boxes, proved risky, because it appears to be very difficult to design a good S-box which will not result in some weird pattern / loop in such a construction - especially for 4 bits).

The main design was allowing a human to work with at most (around) 3 numbers at any given time (not including the key, which would be memorized), allowing a trained human to perform calculations in his/her head. To compensate for this, there is a large number of rounds involved to introduce more security.

### Posting attacks / reporting issues

If you found some kind of attack (even marginally efficient compared to pure brute-force), feel free to reply on reddit (if it is catastrophical) or raise an issue here. I created this because I couldn't find anything like this before, and I don't expect attempt #1 to be strong
