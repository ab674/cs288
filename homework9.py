import libxml2
import sys
import os
import commands
import re
import sys

import MySQLdb

from xml.dom.minidom import parse, parseString

from cStringIO import StringIO
from xml.parsers import expat


def get_elms_for_atr_val(tag, atr, val):
    lst = []
    elms = dom.getElementsByTagName(tag)
    for node in elms:
        if node.childNodes[0].getAttribute(atr) == val:
            lst.append(node)
    return lst

def get_text(e):
    lst = []
    if e.nodeType in (3, 4):
        if e.data != ' ':
            return [e.data]
    else:
        for x in e.childNodes:
            lst = lst + get_text(x)
    return lst

def replace_white_space(str):
    p = re.compile(r'\s+')
    new = p.sub(' ', str)
    return new.strip()

def replace_non_alpha_numeric(s):
    p = re.compile(r'[^a-zA-Z0-9:-]+')
    new = p.sub(' ', s)
    return new.strip()

def html_to_xml(fn):
    xhtml_file = os.system('java -jar tagsoup-1.2.1.jar --files %s' % (fn))
    fn = fn.replace('.html', '.xhtml')
    return fn

def extract_values(dm):
    lst = []
    l = get_elms_for_atr_val('tr', 'class', 'lft')
    for x in l:
        item = get_text(x)
        lst.append(item)
    return lst

def insert_to_db(l, tbl):
    db = MySQLdb.connect(host="localhost", user="root", passwd="", db="stocks")
    c = db.cursor()
    c.execute(
        """CREATE TABLE IF NOT EXISTS `%s` (
        listnumber varchar(50),
        nameandsymbol varchar(250),
        volume varchar(50),
        price varchar(50),
        change varchar(50),
        percentchange varchar(50)
        )""" % (tbl))
    for d in l:
        query = """INSERT INTO `%s` (%s) VALUES('%s','%s','%s','%s','%s','%s');""" % (tbl, ",".join(d.keys()), d['listnumber'], d['nameandsymbol'], d['volume'], d['price'], d['change'], d['percentchange'])
        print query
        c.execute(query)
        db.commit()
    c.close()
    db.close()

def to_dict(l):
    keys = ['listnumber', 'nameandsymbol', 'volume', 'price', 'change', 'percentchange']
    d = [dict(zip(keys, x)) for x in l]
    return d

def main():
    html_fn = sys.argv[1]
    fn = html_fn.replace('.html', '')
    xhtml_fn = html_to_xml(html_fn)
    global dom
    dom = parse(xhtml_fn)
    lst = extract_values(dom)
    lst.pop(0)
    lst = to_dict(lst)
    cursor = insert_to_db(lst, fn)
    return True

if __name__ == "__main__":
    main()
