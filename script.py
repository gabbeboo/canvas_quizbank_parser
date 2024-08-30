import xml.etree.ElementTree as ET

def replace_word_in_xml(file_path, old_word, new_word):
    # Ladda och parsa XML-filen
    tree = ET.parse(file_path)
    root = tree.getroot()

    # Funktion för att ersätta ord i alla textnoder
    def replace_text(node):
        if node.text:
            node.text = node.text.replace(old_word, new_word)
        if node.tail:
            node.tail = node.tail.replace(old_word, new_word)
        for child in node:
            replace_text(child)

    # Starta ersättningen från rot-noden
    replace_text(root)

    # Spara ändringarna tillbaka till filen
    tree.write(file_path, encoding="utf-8", xml_declaration=True)

# Exempel på användning
file_path = 'aritmetik.qti'  # Filens sökväg
replace_word_in_xml(file_path, 'utvärderas', 'evalueras')
