SELECT item_id,
       type,
       text || CASE
                   WHEN type = 'shelf'
                   THEN ' = ' || text2
                   ELSE ''
               END AS Msg
FROM items
WHERE
 -- item_id = 761 AND
    type IN ( 'branch'
            , 'address'
            , 'beginend'
            , 'if'
            , 'insertion'
            , 'select'
            , 'shelf'
            , 'commentin'
            )
;
