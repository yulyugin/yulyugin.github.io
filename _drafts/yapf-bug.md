
test.py:

```python
# Works
a: tuple[tuple, tuple] = (tuple([1, 2]), tuple([3, 4]))

# Crashes
a: tuple[tuple, tuple] = tuple([1, 2]), tuple([3, 4])
```

```console
yapf3 -i test.py 
Traceback (most recent call last):
  File "/usr/lib/python3/dist-packages/yapf/yapflib/pytree_utils.py", line 119, in ParseCodeToTree
    tree = parser_driver.parse_string(code, debug=False)
  File "/usr/lib/python3.10/lib2to3/pgen2/driver.py", line 103, in parse_string
    return self.parse_tokens(tokens, debug)
  File "/usr/lib/python3.10/lib2to3/pgen2/driver.py", line 71, in parse_tokens
    if p.addtoken(type, value, (prefix, start)):
  File "/usr/lib/python3.10/lib2to3/pgen2/parse.py", line 162, in addtoken
    raise ParseError("bad input", type, value, context)
lib2to3.pgen2.parse.ParseError: bad input: type=12, value=',', context=('', (5, 38))

During handling of the above exception, another exception occurred:

Traceback (most recent call last):
  File "/usr/lib/python3/dist-packages/yapf/yapflib/yapf_api.py", line 183, in FormatCode
    tree = pytree_utils.ParseCodeToTree(unformatted_source)
  File "/usr/lib/python3/dist-packages/yapf/yapflib/pytree_utils.py", line 125, in ParseCodeToTree
    tree = parser_driver.parse_string(code, debug=False)
  File "/usr/lib/python3.10/lib2to3/pgen2/driver.py", line 103, in parse_string
    return self.parse_tokens(tokens, debug)
  File "/usr/lib/python3.10/lib2to3/pgen2/driver.py", line 71, in parse_tokens
    if p.addtoken(type, value, (prefix, start)):
  File "/usr/lib/python3.10/lib2to3/pgen2/parse.py", line 162, in addtoken
    raise ParseError("bad input", type, value, context)
lib2to3.pgen2.parse.ParseError: bad input: type=12, value=',', context=('', (5, 38))

During handling of the above exception, another exception occurred:

Traceback (most recent call last):
  File "/usr/lib/python3/dist-packages/yapf/__init__.py", line 225, in _FormatFile
    reformatted_code, encoding, has_change = yapf_api.FormatFile(
  File "/usr/lib/python3/dist-packages/yapf/yapflib/yapf_api.py", line 96, in FormatFile
    reformatted_source, changed = FormatCode(
  File "/usr/lib/python3/dist-packages/yapf/yapflib/yapf_api.py", line 186, in FormatCode
    raise errors.YapfError(errors.FormatErrorMsg(e))
  File "/usr/lib/python3/dist-packages/yapf/yapflib/errors.py", line 37, in FormatErrorMsg
    return '{}:{}:{}: {}'.format(e.args[1][0], e.args[1][1], e.args[1][2], e.msg)
IndexError: tuple index out of range

During handling of the above exception, another exception occurred:

Traceback (most recent call last):
  File "/usr/bin/yapf3", line 33, in <module>
    sys.exit(load_entry_point('yapf==0.32.0', 'console_scripts', 'yapf')())
  File "/usr/lib/python3/dist-packages/yapf/__init__.py", line 360, in run_main
    sys.exit(main(sys.argv))
  File "/usr/lib/python3/dist-packages/yapf/__init__.py", line 124, in main
    changed = FormatFiles(
  File "/usr/lib/python3/dist-packages/yapf/__init__.py", line 202, in FormatFiles
    changed |= _FormatFile(filename, lines, style_config, no_local_style,
  File "/usr/lib/python3/dist-packages/yapf/__init__.py", line 236, in _FormatFile
    raise errors.YapfError(errors.FormatErrorMsg(e))
  File "/usr/lib/python3/dist-packages/yapf/yapflib/errors.py", line 37, in FormatErrorMsg
    return '{}:{}:{}: {}'.format(e.args[1][0], e.args[1][1], e.args[1][2], e.msg)
IndexError: tuple index out of range
```
