import prisma from "../../../lib/prisma";

export default async function createItem(req, res) {
    
    const { 
        name,
        description,
        start_time,
        posted_by_id,
     } = req.body;

    const result = await prisma.item.create({
        data: {
            name: name,
            description: description,
            start_time: start_time,
            posted_by_id: posted_by_id,
        },
    });

    console.log(result);
    res.json(result);
}